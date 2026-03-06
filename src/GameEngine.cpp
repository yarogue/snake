#include "GameEngine.hpp"
#include <chrono>
#include <ncurses.h>
#include <thread>

GameEngine GameEngine::create(const Level &level) {
  GameEngine engine;

  // Seting level and creating board
  engine.currentLevel = level;
  engine.board = Board::create(level.boardWidth, level.boardHeight);

  // Creating snake at center o board, facing RIGHT
  engine.snake =
      Snake::create(Position{level.boardWidth / 2, level.boardHeight / 2},
                    Direction::RIGHT, level.initialSnakeLen);

  // Initializing game state
  engine.score = 0;
  engine.running = true;
  engine.paused = false;

  // Initializing renderer and set timeout
  engine.renderer.init();
  timeout(level.tickIntervalMs);

  // Generating obstacles (avoiding snake + safe zone around it)
  std::vector<Position> forbidden(engine.snake.body.begin(),
                                  engine.snake.body.end());

  // Add a safe zone around the snake so obstacles don't spawn too close
  Position center{level.boardWidth / 2, level.boardHeight / 2};
  for (int dx = -5; dx <= 5; ++dx) {
    for (int dy = -3; dy <= 3; ++dy) {
      forbidden.push_back(Position{center.x + dx, center.y + dy});
    }
  }

  engine.board.generateObstacles(level.obstacleCount, forbidden);

  // Spawning food
  engine.spawnFood();

  return engine;
}

void GameEngine::run() {
  while (running) {
    update();
    // Draw everything
    renderer.drawBoard(board);
    renderer.drawFood(foodPos);
    renderer.drawSnake(snake);
    renderer.drawHUD(score, currentLevel.levelNumber, board);

    // Show pause overlay if paused
    if (paused) {
      renderer.drawPaused(board);
    }
  }
  // Clean up after game end
  renderer.shutdown();
}

void GameEngine::update() {
  int key = getch();
  if (inputHandler.isQuitKey(key)) {
    running = false;
    return;
  }

  // Toggle pause on 'p' or 'P'
  if (key == 'p' || key == 'P') {
    paused = !paused;
    return;
  }

  // Skip game logic while paused
  if (paused)
    return;

  auto dir = inputHandler.pollInput(key);
  if (dir.has_value()) {
    snake.setDirection(dir.value());
  }
  snake.move();
  Position wrappedHead = board.wrap(snake.getHead());
  snake.body.pop_front();
  snake.body.push_front(wrappedHead);
  if (snake.isCollidingWithSelf()) {
    handleDeath();
    return;
  }
  if (checkWallOrObstacleCollision()) {
    handleDeath();
    return;
  }
  handleFoodEaten();
}

// Other GameEngine methods

void GameEngine::spawnFood() {
  bool validPosition = false;
  while (!validPosition) {
    Position candidate{rand() % board.width, rand() % board.height};
    bool isSnakeBody = false;
    for (const auto &segment : snake.body) {
      if (segment == candidate) {
        isSnakeBody = true;
        break;
      }
    }
    if (!isSnakeBody && !board.isObstacle(candidate)) {
      foodPos = candidate;
      validPosition = true;
    }
  }
}

bool GameEngine::checkWallOrObstacleCollision() const {
  return board.isObstacle(snake.getHead());
}

bool GameEngine::checkSelfCollision() const {
  return snake.isCollidingWithSelf();
}

void GameEngine::handleFoodEaten() {
  if (snake.getHead() == foodPos) {
    snake.grow();
    score++;
    spawnFood();
  }
}

void GameEngine::handleDeath() {
  renderer.drawBoard(board);
  renderer.drawSnake(snake);
  renderer.drawGameOver(board);

  // End game
  running = false;
}