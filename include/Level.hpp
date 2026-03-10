#pragma once
#include <string>
#include <utility>
#include <vector>

struct Level {
  int levelNumber;
  int boardWidth;
  int boardHeight;
  int obstacleCount;
  int initialSnakeLen;
  int tickIntervalMs;
  int puzzlesToSolve;
  std::vector<std::pair<std::string, std::string>> puzzles; // {word, hint}
};
