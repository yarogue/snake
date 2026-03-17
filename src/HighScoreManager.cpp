#include "HighScoreManager.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace HighScoreManager {

  //loadHighScores
  HighScoreEntry *loadHighScores(const std::string &filename, int &count) {

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

void freeHighScores(HighScoreEntry *entries) {

  delete[] entries;
}

} // namespace HighScoreManager
