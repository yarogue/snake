#pragma once
// #include <string>
// #include <vector>

// ============================================================
// TODO 1f — Level struct
// ============================================================
// A Level holds all the configuration that controls how hard
// the game is and how the board is set up.
//
// MEMBERS:
//   int   levelNumber;       // 1, 2, 3, ...
//   int   boardWidth;        // number of columns (e.g. 20)
//   int   boardHeight;       // number of rows    (e.g. 20)
//   int   obstacleCount;     // how many stones to spawn
//   int   initialSnakeLen;   // how long the snake starts
//   int   tickIntervalMs;    // milliseconds between game ticks
//                            //   smaller = faster = harder
//
// No methods needed now. GameEngine reads these values at startup.
//
// HINT FOR LATER (word-game extension):
//   You will add something like:
//     std::vector<std::string> wordList;
//     std::vector<std::string> clueList;
//   For now, leave them commented out.
//
// FACTORY IDEAS (optional, for later):
//   You could add static Level easy(), Level medium(), Level hard()
//   factory functions that return pre-configured Level structs.
// ============================================================

struct Level {
  // TODO 1f-1: declare levelNumber, boardWidth, boardHeight
  // TODO 1f-2: declare obstacleCount, initialSnakeLen, tickIntervalMs

  // TODO 1f-3 (OPTIONAL): add static factory functions
  //   static Level easy();
  //   static Level medium();
  //   static Level hard();
};
