#pragma once
#include <string>

// ============================================================
// TODO Phase 2 — HighScoreManager (header)
// ============================================================
// This module manages persistent high scores — one per level.
// Scores are saved to data/highscores.txt so they survive
// between program sessions.
//
// WHY a separate module?
//   Clean responsibility: this module ONLY deals with reading
//   and writing score data. GameEngine and Menu can call it
//   without knowing how files work.
//
// FILE FORMAT (data/highscores.txt):
//   level,score,puzzlesSolved
//   1,0,0
//   2,0,0
//   3,0,0
//
// DATA STRUCTURE:
//   struct HighScoreEntry {
//     int level;
//     int score;
//     int puzzlesSolved;
//   };
//
// FUNCTIONS to implement (in HighScoreManager.cpp):
//
//   HighScoreEntry* loadHighScores(const std::string& filename, int& count)
//     → Open file, count lines, allocate array with new[].
//     → Parse each line: split by ',' → fill entry fields.
//     → Set count to number of entries loaded.
//     → Return pointer to the array.
//     → If file fails, return nullptr and set count = 0.
//
//   void saveHighScore(const std::string& filename,
//                      int level, int score, int puzzlesSolved)
//     → Load existing scores into array.
//     → Find the entry matching 'level'.
//     → If new score > existing score, update it.
//     → Write ALL entries back to file.
//     → Free the loaded array.
//
//   void printHighScores(const std::string& filename)
//     → Load scores, print a formatted table to cout.
//     → Free the loaded array.
//
//   void freeHighScores(HighScoreEntry* entries)
//     → Call: delete[] entries;
//     → This pairs with the new[] in loadHighScores().
// ============================================================

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
