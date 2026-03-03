// #include "GameEngine.hpp"
// #include "Level.hpp"

// ============================================================
// TODO 6a — main.cpp  (entry point)
// ============================================================
// This is where the game starts. It should be SHORT and clean.
// All the real logic lives in GameEngine.
//
// STEPS:
//
// TODO 6a-1: Show a start-up menu
//   Print to console (BEFORE ncurses starts):
//     "=== SNAKE GAME ==="
//     "Select level:"
//     "  1. Easy"
//     "  2. Medium"
//     "  3. Hard"
//     "Enter choice: "
//   Read a single char or int from std::cin.
//
// TODO 6a-2: Build the Level based on player choice
//   if choice == 1 → level = Level{ 1, 20, 20, 5, 3, 200 }
//   if choice == 2 → level = Level{ 2, 20, 20, 10, 3, 130 }
//   if choice == 3 → level = Level{ 3, 20, 20, 18, 3, 70  }
//   (fields are: levelNumber, boardWidth, boardHeight,
//                obstacleCount, initialSnakeLen, tickIntervalMs)
//   Once you implement Level factory functions (TODO 1f-3),
//   replace these with Level::easy(), Level::medium(), Level::hard()
//
// TODO 6a-3: Create and run the engine
//   GameEngine engine = GameEngine::create(level)
//   engine.run()
//
// TODO 6a-4: Return 0
//   return 0;

int main() {
  // TODO 6a-1: show menu, read choice

  // TODO 6a-2: build Level from choice

  // TODO 6a-3: create and run GameEngine

  return 0;
}