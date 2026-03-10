#include "LevelLoader.hpp"
#include <fstream>
#include <iostream>

namespace LevelLoader {


// Loading level
Level *loadLevel(const std::string &filename) {

  std::string line;

  std::ifstream file(filename);

  // is file opened check
  if (!file.is_open()) {
    std::cout << "Error: could not open file!" << std::endl;
    return nullptr;
  }

  // new level object alloc
  auto level = new Level;

  // default values init
  level->levelNumber     = 0;
  level->boardWidth      = 0;
  level->boardHeight     = 0;
  level->obstacleCount   = 0;
  level->initialSnakeLen = 0;
  level->tickIntervalMs  = 0;
  level->puzzlesToSolve  = 0;

  bool readingPuzzles = false;

  // Read lines in loop
  while (std::getline(file, line)) {
    // Step 4a: Skip empty lines
    if (line.empty()) continue;

    //  Check for [puzzles] marker
    if (line == "[puzzles]") {
      readingPuzzles = true;
      continue;
    }

    // Puzzle mode - read word|hint pairs
    if (readingPuzzles) {
      size_t pipePos = line.find('|');
      if (pipePos != std::string::npos) {
        std::string word = line.substr(0, pipePos);
        std::string hint = line.substr(pipePos + 1);
        level->puzzles.emplace_back(word, hint);
      }
    }
    // Config mode - read key=value pairs
    else {
      size_t eqPos = line.find('=');
      if (eqPos != std::string::npos) {
        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Match key to level fields
        if (key == "levelNumber") {
          level->levelNumber = std::stoi(value);
        } else if (key == "boardWidth") {
          level->boardWidth = std::stoi(value);
        } else if (key == "boardHeight") {
          level->boardHeight = std::stoi(value);
        } else if (key == "obstacleCount") {
          level->obstacleCount = std::stoi(value);
        } else if (key == "initialSnakeLen") {
          level->initialSnakeLen = std::stoi(value);
        } else if (key == "tickIntervalMs") {
          level->tickIntervalMs = std::stoi(value);
        } else if (key == "puzzlesToSolve") {
          level->puzzlesToSolve = std::stoi(value);
        }
      }
    }
  }

  file.close();

  return level;
}

// Validate level
bool validateLevel(const Level *level) {

  if (level == nullptr)            {return false;}
  if (level->boardWidth <= 0)      {return false;}
  if (level->boardHeight <= 0)     {return false;}
  if (level->obstacleCount < 0)    {return false;}
  if (level->initialSnakeLen <= 0) {return false;}
  if (level->tickIntervalMs <= 0)  {return false;}
  if (level->puzzlesToSolve <= 0)  {return false;}
  if (level->puzzles.empty())      {return false;}

  return true;
}

void freeLevel(const Level *level) {
    delete level;
}

} // namespace LevelLoader