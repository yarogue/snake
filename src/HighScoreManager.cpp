#include "HighScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// ============================================================
// TODO Phase 2 — HighScoreManager (implementation)
// ============================================================
// Implement the four functions declared in HighScoreManager.hpp.
// Read the header file TODOs for detailed pseudocode.
// ============================================================

namespace HighScoreManager {

// ────────────────────────────────────────────
// TODO 2a — loadHighScores
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Open file with std::ifstream
//   2. If open fails → set count = 0 → return nullptr
//   3. First pass: count how many lines are in the file
//      HINT: read lines into a std::vector<std::string> so you
//            only need to read the file once.
//   4. Allocate array: HighScoreEntry* entries = new HighScoreEntry[count];
//   5. For each stored line:
//      a. Create std::stringstream from the line
//      b. Read three comma-separated values:
//         std::getline(ss, token, ',') → entries[i].level = stoi(token)
//         std::getline(ss, token, ',') → entries[i].score = stoi(token)
//         std::getline(ss, token, ',') → entries[i].puzzlesSolved = stoi(token)
//   6. Return entries
// ────────────────────────────────────────────
HighScoreEntry *loadHighScores(const std::string &filename, int &count) {
  // TODO: implement
  count = 0;
  return nullptr;
}

// ────────────────────────────────────────────
// TODO 2b — saveHighScore
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Load existing scores with loadHighScores()
//   2. Find the entry where entry.level == level
//   3. If new score > entry.score → update entry.score and entry.puzzlesSolved
//   4. Open file with std::ofstream (this overwrites)
//   5. Write each entry as: level,score,puzzlesSolved\n
//   6. Close file
//   7. Call freeHighScores() to release the array
// ────────────────────────────────────────────
void saveHighScore(const std::string &filename, int level, int score,
                   int puzzlesSolved) {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 2c — printHighScores
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Load scores with loadHighScores()
//   2. If nullptr → print "No high scores yet." → return
//   3. Print header: "=== HIGH SCORES ==="
//   4. Print column headers: "Level | Score | Puzzles"
//   5. For each entry → print formatted row
//   6. Call freeHighScores() to release the array
// ────────────────────────────────────────────
void printHighScores(const std::string &filename) {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 2d — freeHighScores
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Call: delete[] entries;
//   This pairs with new[] in loadHighScores().
// ────────────────────────────────────────────
void freeHighScores(HighScoreEntry *entries) {
  // TODO: implement
}

} // namespace HighScoreManager
