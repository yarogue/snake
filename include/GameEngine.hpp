#pragma once
// #include "Board.hpp"
// #include "Snake.hpp"
// #include "Level.hpp"
// #include "Renderer.hpp"
// #include "InputHandler.hpp"
// #include "Position.hpp"

// ============================================================
// TODO 5a — GameEngine struct  (header)
// ============================================================
// GameEngine is the brain of the game.
// It owns all the game objects and coordinates the game loop.
//
// MEMBERS:
//   Board        board;
//   Snake        snake;
//   Level        currentLevel;
//   Renderer     renderer;
//   InputHandler inputHandler;
//   Position     foodPos;
//   int          score;
//   bool         running;
//
// METHODS to declare (implement in GameEngine.cpp):
//
//   static GameEngine create(const Level& level)
//     → Factory: initialize board, snake, renderer, etc.
//       from the Level config. Return a ready-to-run GameEngine.
//
//   void run()
//     → The main game loop. Keeps running until running == false.
//
//   void update()
//     → Called once per tick. Handles:
//         - reading input
//         - moving the snake
//         - checking all collisions
//         - spawning food if eaten
//
//   void spawnFood()
//     → Pick a random empty Position (not snake body, not obstacle)
//       and set foodPos to it.
//
//   bool checkWallOrObstacleCollision() const
//     → TOROIDAL: no wall death! Walls wrap.
//     → But obstacles kill: return true if snake head is on an obstacle.
//
//   bool checkSelfCollision() const
//     → Delegate to snake.isCollidingWithSelf()
//
//   void handleFoodEaten()
//     → If snake head == foodPos:
//         snake.grow()
//         score += 10  (or some amount)
//         spawnFood()
//
//   void handleDeath()
//     → Set running = false
//     → renderer.drawGameOver()
// ============================================================

struct GameEngine {
  // TODO 5a-1: declare all members listed above

  // TODO 5a-2: declare all method signatures listed above
};
