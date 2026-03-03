// #include "GameEngine.hpp"
// #include <chrono>
// #include <thread>

// ============================================================
// TODO 5b — GameEngine::create()  (static factory)
// ============================================================
// TODO 5b-1:
//   GameEngine engine
//   engine.currentLevel = level
//   engine.board  = Board::create(level.boardWidth, level.boardHeight)
//   engine.snake  = Snake::create(
//                       Position{ level.boardWidth/2, level.boardHeight/2 },
//                       Direction::RIGHT,
//                       level.initialSnakeLen)
//   engine.score   = 0
//   engine.running = true
//   engine.renderer.init()
//   Set ncurses timeout: timeout(level.tickIntervalMs)
//
//   Collect forbidden positions = all snake body positions
//   engine.board.generateObstacles(level.obstacleCount, forbidden)
//   engine.spawnFood()
//   return engine

// ============================================================
// TODO 5c — GameEngine::run()
// ============================================================
// TODO 5c-1:
//   while (running):
//     engine.update()
//     Draw everything:
//       renderer.drawBoard(board)
//       renderer.drawFood(foodPos)
//       renderer.drawSnake(snake)
//       renderer.drawHUD(score, currentLevel.levelNumber)
//   After loop exits:
//     renderer.shutdown()

// ============================================================
// TODO 5d — GameEngine::update()
// ============================================================
// TODO 5d-1:
//   1. Poll input: auto dir = inputHandler.pollInput()
//      If dir has a value → snake.setDirection(dir.value())
//      Also poll for quit key: if raw getch() == 'q' → running = false; return
//      HINT: you may need to store the last raw key separately.
//            Or integrate quit check into pollInput() returning a special
//            result.
//
//   2. Move snake one step: snake.move()
//      THEN apply toroidal wrap to the new head:
//        Position head = board.wrap(snake.getHead())
//        Manually update snake body front to the wrapped head.
//        HINT: think about how to do this — you may need a helper
//              method Snake::setHead(Position p), or adjust move() itself
//              to call board.wrap() on the new head.
//              Discuss your design choice here!
//
//   3. Check self-collision:
//      if snake.isCollidingWithSelf() → handleDeath(); return
//
//   4. Check obstacle collision:
//      if checkWallOrObstacleCollision() → handleDeath(); return
//
//   5. Check food eaten:
//      handleFoodEaten()

// ============================================================
// TODO 5e — Other GameEngine methods
// ============================================================

// --- GameEngine::spawnFood() ---
// TODO 5e-1:
//   Repeat until a valid position is found:
//     candidate = Position{ rand() % board.width, rand() % board.height }
//     Check it is NOT any snake body cell
//     Check it is NOT an obstacle
//     If valid → foodPos = candidate; return

// --- GameEngine::checkWallOrObstacleCollision() ---
// TODO 5e-2:
//   (Walls don't kill — toroidal. Only obstacles do.)
//   return board.isObstacle(snake.getHead())

// --- GameEngine::checkSelfCollision() ---
// TODO 5e-3:
//   return snake.isCollidingWithSelf()

// --- GameEngine::handleFoodEaten() ---
// TODO 5e-4:
//   if snake.getHead() == foodPos:
//     snake.grow()            ← grow instead of normal move
//     score += 10
//     spawnFood()

// --- GameEngine::handleDeath() ---
// TODO 5e-5:
//   renderer.drawBoard(board)
//   renderer.drawSnake(snake)
//   renderer.drawGameOver()
//   running = false
