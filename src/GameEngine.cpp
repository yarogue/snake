#include "GameEngine.hpp"
#include <cstdlib>
#include <curses.h>

GameEngine GameEngine::create(const Level &level) {
  GameEngine engine;

  engine.currentLevel = level;
  engine.board = Board::create(level.boardWidth, level.boardHeight);

  engine.snake =
      Snake::create(Position{level.boardWidth / 2, level.boardHeight / 2},
                    Direction::RIGHT, level.initialSnakeLen);

  engine.score = 0;
  engine.running = true;
  engine.paused = false;
  engine.lastDeathChoice = 'q';
  engine.puzzlesSolved = 0;
  engine.puzzleIndex = 0;
  engine.puzzlesStartCount = 0;

  engine.renderer.init();
  engine.renderer.offsetX = 1;
  engine.renderer.offsetY = 2;
  timeout(level.tickIntervalMs);

  // Safe zone around the snake
  std::vector<Position> forbidden;
  for (int i = 0; i < engine.snake.body.size(); ++i) {
    forbidden.push_back(engine.snake.body.at(i));
  }
  Position center{level.boardWidth / 2, level.boardHeight / 2};
  for (int dx = -5; dx <= 5; ++dx) {
    for (int dy = -3; dy <= 3; ++dy) {
      forbidden.push_back(Position{center.x + dx, center.y + dy});
    }
  }

  engine.board.generateObstacles(level.obstacleCount, forbidden);

  // Load first puzzle
  engine.nextPuzzle();

  return engine;
}

void GameEngine::run() {
  while (running) {
    update();

    renderer.drawBoard(board);
    renderer.drawSnake(snake);
    renderer.drawHUD(score, currentLevel.levelNumber, board);

    if (paused) {
      renderer.drawPaused(board);
    } else {
      renderer.drawLetters(letters, currentPuzzle);
      renderer.drawPuzzleHUD(currentPuzzle, puzzlesSolved - puzzlesStartCount,
                             currentLevel.puzzlesToSolve, board);
    }
  }
  renderer.shutdown();
}

void GameEngine::update() {
  int key = getch();

  if (inputHandler.isQuitKey(key)) {
    running = false;
    return;
  }

  if (key == 'p' || key == 'P') {
    paused = !paused;
    return;
  }

  // Cycle color palette
  if (key == 'c' || key == 'C') {
    renderer.nextPalette();
    return;
  }

  if (paused)
    return;

  auto dir = inputHandler.pollInput(key);
  if (dir.has_value()) {
    snake.setDirection(dir.value());
  }

  snake.move();
  Position wrappedHead = board.wrap(snake.getHead());
  snake.body.popFront();
  snake.body.pushFront(wrappedHead);

  if (snake.isCollidingWithSelf()) {
    handleDeath();
    return;
  }

  if (checkWallOrObstacleCollision()) {
    handleDeath();
    return;
  }

  handleLetterPickup();

  if (checkLevelComplete()) {
    running = false; // Signal level complete (main.cpp handles progression)
  }
}

void GameEngine::spawnLetters() {
  letters.clear();
  auto missing = currentPuzzle.getMissingLetters();

  // Place correct letters (one per missing unique letter)
  for (char c : missing) {
    bool placed = false;
    int attempts = 0;
    while (!placed && attempts < 100) {
      attempts++;
      Position pos{rand() % board.width, rand() % board.height};

      // Check not on snake, obstacle, or existing letter
      if (snake.body.contains(pos))
        continue;
      if (board.isObstacle(pos))
        continue;
      bool letterCollision = false;
      for (const auto &lp : letters) {
        if (lp.pos == pos) {
          letterCollision = true;
          break;
        }
      }
      if (letterCollision)
        continue;

      letters.push_back(LetterPickup{pos, c});
      placed = true;
    }
  }

  // Add wrong letters to fill up to 5 total
  const char wrongChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#";
  while (letters.size() < 5) {
    char c = wrongChars[rand() % (sizeof(wrongChars) - 1)];
    // Make sure it's not one of the correct missing letters
    if (missing.count(c))
      continue;

    bool placed = false;
    int attempts = 0;
    while (!placed && attempts < 100) {
      attempts++;
      Position pos{rand() % board.width, rand() % board.height};

      if (snake.body.contains(pos))
        continue;
      if (board.isObstacle(pos))
        continue;
      bool letterCollision = false;
      for (const auto &lp : letters) {
        if (lp.pos == pos) {
          letterCollision = true;
          break;
        }
      }
      if (letterCollision)
        continue;

      letters.push_back(LetterPickup{pos, c});
      placed = true;
    }
  }
}

void GameEngine::handleLetterPickup() {
  Position head = snake.getHead();

  for (size_t i = 0; i < letters.size(); ++i) {
    if (letters[i].pos == head) {
      char picked = letters[i].letter;

      // Snake grows on ANY letter pickup
      snake.grow();

      // Check if it's a correct letter
      if (currentPuzzle.revealLetter(picked)) {
        score += 10;
      }

      // Remove picked letter from the board
      letters.erase(letters.begin() + i);

      // If puzzle complete, advance
      if (currentPuzzle.isComplete()) {
        puzzlesSolved++;

        if (!checkLevelComplete()) {
          nextPuzzle();
        }
      } else {
        // Respawn a new letter to keep board populated
        auto missing = currentPuzzle.getMissingLetters();
        const char wrongChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#";

        // Decide: spawn a correct or wrong letter
        char newChar;
        if (!missing.empty() && (rand() % 2 == 0)) {
          // Pick a random missing letter
          auto it = missing.begin();
          std::advance(it, rand() % missing.size());
          newChar = *it;
        } else {
          // Pick a wrong letter
          do {
            newChar = wrongChars[rand() % (sizeof(wrongChars) - 1)];
          } while (missing.count(newChar));
        }

        // Find valid position for new letter
        int attempts = 0;
        while (attempts < 100) {
          attempts++;
          Position pos{rand() % board.width, rand() % board.height};
          if (snake.body.contains(pos))
            continue;
          if (board.isObstacle(pos))
            continue;
          bool letterCollision = false;
          for (const auto &lp : letters) {
            if (lp.pos == pos) {
              letterCollision = true;
              break;
            }
          }
          if (letterCollision)
            continue;

          letters.push_back(LetterPickup{pos, newChar});
          break;
        }
      }

      break; // Only pick up one letter per tick
    }
  }
}

void GameEngine::nextPuzzle() {
  if (puzzleIndex < (int)currentLevel.puzzles.size()) {
    auto &p = currentLevel.puzzles[puzzleIndex];
    currentPuzzle = WordPuzzle::create(p.first, p.second);
    puzzleIndex++;

    if (letters.empty()) {
      // First puzzle — spawn everything fresh
      spawnLetters();
    } else {
      // Keep existing letters, but handle conflicts
      auto missing = currentPuzzle.getMissingLetters();
      const char wrongChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#";

      // Replace any existing letters that are now correct for new puzzle
      for (auto &lp : letters) {
        if (missing.count(lp.letter)) {
          char newChar;
          do {
            newChar = wrongChars[rand() % (sizeof(wrongChars) - 1)];
          } while (missing.count(newChar));
          lp.letter = newChar;
        }
      }

      // Spawn the correct letters for the new puzzle
      for (char c : missing) {
        int attempts = 0;
        while (attempts < 100) {
          attempts++;
          Position pos{rand() % board.width, rand() % board.height};
          if (snake.body.contains(pos))
            continue;
          if (board.isObstacle(pos))
            continue;
          bool letterCollision = false;
          for (const auto &lp : letters) {
            if (lp.pos == pos) {
              letterCollision = true;
              break;
            }
          }
          if (letterCollision)
            continue;

          letters.push_back(LetterPickup{pos, c});
          break;
        }
      }
    }
  }
}

bool GameEngine::checkLevelComplete() const {
  int solvedThisLevel = puzzlesSolved - puzzlesStartCount;
  return solvedThisLevel >= currentLevel.puzzlesToSolve;
}

bool GameEngine::checkWallOrObstacleCollision() const {
  return board.isObstacle(snake.getHead());
}

bool GameEngine::checkSelfCollision() const {
  return snake.isCollidingWithSelf();
}

void GameEngine::handleDeath() {
  renderer.drawBoard(board);
  renderer.drawSnake(snake);
  lastDeathChoice = renderer.drawGameOver(board, score, puzzlesSolved);
  running = false;
}

bool GameEngine::wantsRestart() const { return lastDeathChoice == 'r'; }