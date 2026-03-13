#pragma once
#include <string>

struct HighScoreEntry {
  int level;
  int score;
  int puzzlesSolved;
};

namespace HighScoreManager {

HighScoreEntry *loadHighScores(const std::string &filename, int &count);
void saveHighScore(const std::string &filename, int level, int score,
                   int puzzlesSolved);
void printHighScores(const std::string &filename);
void freeHighScores(HighScoreEntry *entries);

} // namespace HighScoreManager
