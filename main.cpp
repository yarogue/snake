#include "LevelLoader.hpp"
#include "HighScoreManager.hpp"
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

  // ---- TEST: LevelLoader ----
  const int LEVEL_COUNT = 3;
  std::string levelFiles[LEVEL_COUNT] = {
    "data/level1.txt", "data/level2.txt", "data/level3.txt"};

  Level *levels[LEVEL_COUNT];

  for (int i = 0; i < LEVEL_COUNT; i++) {
    levels[i] = LevelLoader::loadLevel(levelFiles[i]);

    if (levels[i] == nullptr) {
      std::cout << "ERROR: Failed to load " << levelFiles[i] << std::endl;
      return 1;
    }

    if (!LevelLoader::validateLevel(levels[i])) {
      std::cout << "ERROR: Validation failed for " << levelFiles[i]
                << std::endl;
      return 1;
    }

    // Printing loaded data to verify
    std::cout << "--- Level " << levels[i]->levelNumber << " ---" << std::endl;
    std::cout << "  Board: " << levels[i]->boardWidth << "x"
              << levels[i]->boardHeight << std::endl;
    std::cout << "  Obstacles: " << levels[i]->obstacleCount << std::endl;
    std::cout << "  Snake len: " << levels[i]->initialSnakeLen << std::endl;
    std::cout << "  Tick: " << levels[i]->tickIntervalMs << "ms" << std::endl;
    std::cout << "  Puzzles to solve: " << levels[i]->puzzlesToSolve
              << std::endl;
    std::cout << "  Puzzles loaded: " << levels[i]->puzzles.size() << std::endl;
    std::cout << "  First puzzle: " << levels[i]->puzzles[0].first << " | "
              << levels[i]->puzzles[0].second << std::endl;
    std::cout << std::endl;
  }

  // Cleanups
  for (auto & level : levels) {
    LevelLoader::freeLevel(level);
  }
  std::cout << "All levels loaded, validated, and freed successfully.\n\n";

  // ---- TEST: HighScoreManager ----
  const std::string highScoreFile = "data/highscores.txt";

  std::cout << "Before saving:\n";
  HighScoreManager::printHighScores(highScoreFile);

  std::cout << "\nSaving score: level=1, score=250, puzzles=5\n";
  HighScoreManager::saveHighScore(highScoreFile, 1, 250, 5);

  std::cout << "\nAfter saving:\n";
  HighScoreManager::printHighScores(highScoreFile);

  return 0;
}