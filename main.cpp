#include "LevelLoader.hpp"
#include "Menu.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// ============================================================
// TODO Phase 3 — Refactored main.cpp
// ============================================================
// The old main.cpp had ALL level data hardcoded (puzzles, config).
// The new main.cpp is minimal:
//   1. Seed random
//   2. Load levels from external files using LevelLoader
//   3. Validate each level
//   4. Run the menu loop
//   5. Free all level memory
//
// PSEUDOCODE:
//   1. srand(time(nullptr));
//
//   2. Define level file paths:
//      const int LEVEL_COUNT = 3;
//      std::string levelFiles[LEVEL_COUNT] = {
//        "data/level1.txt", "data/level2.txt", "data/level3.txt"
//      };
//      std::string highScoreFile = "data/highscores.txt";
//
//   3. Load levels into a pointer array:
//      Level* levels[LEVEL_COUNT];
//      for (int i = 0; i < LEVEL_COUNT; i++):
//        levels[i] = LevelLoader::loadLevel(levelFiles[i]);
//        if (levels[i] == nullptr):
//          print error, free already loaded levels, return 1
//        if (!LevelLoader::validateLevel(levels[i])):
//          print error, free all loaded levels, return 1
//
//   4. Run the menu:
//      Menu::menuLoop(levels, LEVEL_COUNT, highScoreFile);
//
//   5. Cleanup — free all levels:
//      for (int i = 0; i < LEVEL_COUNT; i++):
//        LevelLoader::freeLevel(levels[i]);
//
//   6. return 0;
// ============================================================

int main() {
  srand(time(nullptr));

  // TODO: implement the pseudocode above
  // STEP 1: Define file paths
  // STEP 2: Load levels with LevelLoader::loadLevel()
  // STEP 3: Validate each level with LevelLoader::validateLevel()
  // STEP 4: Run Menu::menuLoop()
  // STEP 5: Free all levels with LevelLoader::freeLevel()

  return 0;
}