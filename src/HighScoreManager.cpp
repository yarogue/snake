#include "HighScoreManager.hpp"

#include <algorithm>
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


  //loadHighScores
  HighScoreEntry *loadHighScores(const std::string &filename, int &count) {
    // 1. Open file with std::ifstream
    std::ifstream file(filename);

    if (!file.is_open()) {
      count = 0;
      return nullptr;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) {
        lines.push_back(line);
      }
    }

    count = lines.size();

    if (count == 0) {
      return nullptr;
    }

    // Allocate array
    auto* entries = new HighScoreEntry[count];

    // For each stored line:
    for (int i = 0; i < count; ++i) {

      std::stringstream ss(lines[i]);
      std::string token;

      std::getline(ss, token, ',');
      entries[i].level = std::stoi(token);

      std::getline(ss, token, ',');
      entries[i].score = std::stoi(token);

      std::getline(ss, token, ',');
      entries[i].puzzlesSolved = std::stoi(token);
    }

    // Returning entries
    return entries;
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
void saveHighScore(const std::string &filename, const int level, const int score,
                   const int puzzlesSolved) {

    int count = 0;

    HighScoreEntry* entries = loadHighScores(filename, count);

    if (entries == nullptr) {
      return;
    }

    for (int i = 0; i < count; ++i) {
      if (entries[i].level == level) {

        if (score > entries[i].score) {
          entries[i].score = score;
          entries[i].puzzlesSolved = puzzlesSolved;
        }

        break;
      }
    }

  if (std::ofstream outFile(filename); outFile.is_open()) {
      for (int i = 0; i < count; ++i) {
        outFile << entries[i].level << ","
                << entries[i].score << ","
                << entries[i].puzzlesSolved << "\n";
      }

      outFile.close();
    }

    freeHighScores(entries);
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

    int count = 0;

    HighScoreEntry* entries = loadHighScores(filename, count);

    if (entries == nullptr) {
      std::cout << "No high scores yet.\n";
      return;
    }

    std::cout << "=== HIGH SCORES ===\n";

    std::cout << "Level | Score | Puzzles\n";

    for (int i = 0; i < count; ++i) {
      std::cout << entries[i].level << " | "
                << entries[i].score << " | "
                << entries[i].puzzlesSolved << "\n";
    }

    freeHighScores(entries);
}

// ────────────────────────────────────────────
// TODO 2d — freeHighScores
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Call: delete[] entries;
//   This pairs with new[] in loadHighScores().
// ────────────────────────────────────────────
void freeHighScores(HighScoreEntry *entries) {

  delete[] entries;
}

} // namespace HighScoreManager
