#include "LevelLoader.hpp"
#include "HighScoreManager.hpp"
#include "Menu.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif


int main() {

#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  srand(time(nullptr));
  constexpr int LEVEL_COUNT = 3;

  std::string levelFiles[LEVEL_COUNT] = {
    "data/level1.txt", "data/level2.txt", "data/level3.txt"};
  const std::string highScoreFile = "data/highscores.txt";
  Level *levels[LEVEL_COUNT];

  // Load & validate all levels
  for (int i = 0; i < LEVEL_COUNT; i++) {
    levels[i] = LevelLoader::loadLevel(levelFiles[i]);
    if (levels[i] == nullptr) {
      std::cout << "ERROR: Failed to load " << levelFiles[i] << std::endl;
      return 1;
    }
    if (!LevelLoader::validateLevel(levels[i])) {
      std::cout << "ERROR: Validation failed for " << levelFiles[i] << std::endl;
      return 1;
    }
  }
  // Run the menu
  Menu::menuLoop(levels, LEVEL_COUNT, highScoreFile);

  // Cleanup
  for (auto & level : levels) {
    LevelLoader::freeLevel(level);
  }

  return 0;
}
