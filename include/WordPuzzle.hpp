#pragma once
#include <set>
#include <string>
#include <vector>

struct WordPuzzle {
  std::string word;           // "HORSE"
  std::string hint;           // "An animal the knight travels on"
  std::vector<bool> revealed; // which letters are visible

  // Get display string like "H___E"
  std::string getDisplay() const {
    std::string display;
    for (size_t i = 0; i < word.size(); ++i) {
      display += revealed[i] ? word[i] : '_';
    }
    return display;
  }

  // Check if puzzle is fully solved
  bool isComplete() const {
    for (bool r : revealed) {
      if (!r)
        return false;
    }
    return true;
  }

  // Try to reveal a letter. Returns true if it was a correct missing letter.
  bool revealLetter(char c) {
    bool found = false;
    char upper = (c >= 'a' && c <= 'z') ? (c - 32) : c;
    for (size_t i = 0; i < word.size(); ++i) {
      if (!revealed[i] && word[i] == upper) {
        revealed[i] = true;
        found = true;
      }
    }
    return found;
  }

  // Get the set of letters that are still missing
  std::set<char> getMissingLetters() const {
    std::set<char> missing;
    for (size_t i = 0; i < word.size(); ++i) {
      if (!revealed[i]) {
        missing.insert(word[i]);
      }
    }
    return missing;
  }

  // Factory: create a puzzle, revealing the first and last letter
  static WordPuzzle create(const std::string &word, const std::string &hint) {
    WordPuzzle p;
    p.word = word;
    p.hint = hint;
    p.revealed.resize(word.size(), false);

    // Reveal first and last letter
    if (!word.empty()) {
      p.revealed[0] = true;
      p.revealed[word.size() - 1] = true;
    }
    return p;
  }
};
