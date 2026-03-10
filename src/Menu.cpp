#include "Menu.hpp"
#include "GameEngine.hpp"
#include "HighScoreManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

// ============================================================
// TODO Phase 3 — Menu (implementation)
// ============================================================
// Implement the functions declared in Menu.hpp.
// Read the header file TODOs for detailed pseudocode.
// ============================================================

namespace Menu {

// ────────────────────────────────────────────
// TODO 3a — showMenu
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Print the banner and commands using std::cout
//   2. Print "> " prompt (no newline) so user can type
// ────────────────────────────────────────────
void showMenu() {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 3b — menuLoop
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. while (true):
//      a. Call showMenu()
//      b. Read full line: std::getline(std::cin, input)
//      c. Extract first word as command
//         HINT: std::stringstream ss(input); ss >> command;
//      d. if command == "play":
//           - Try to extract level number: ss >> levelNum
//           - If no number given, default to 1
//           - Validate levelNum is 1..levelCount
//           - Call handlePlay(levels, levelCount, levelNum-1, highScoreFile)
//         else if command == "highscores":
//           - Call HighScoreManager::printHighScores(highScoreFile)
//         else if command == "settings":
//           - Call handleSettings()
//         else if command == "quit":
//           - Print "Goodbye!"
//           - break
//         else:
//           - Print "Unknown command. Type 'quit' to exit."
// ────────────────────────────────────────────
void menuLoop(Level *levels[], int levelCount,
              const std::string &highScoreFile) {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 3c — handlePlay
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. int carryPuzzles = 0;
//   2. for (int i = startLevel; i < levelCount;):
//      a. GameEngine* engine = new GameEngine;
//         *engine = GameEngine::create(levels[i]);
//         // OR refactor create() to return GameEngine*
//      b. engine->puzzlesSolved = carryPuzzles;
//         engine->puzzlesStartCount = carryPuzzles;
//      c. engine->run();
//      d. carryPuzzles = engine->puzzlesSolved;
//      e. bool completed = engine->checkLevelComplete();
//      f. bool restart = engine->wantsRestart();
//      g. int score = engine->score;
//      h. delete engine;  // free the memory!
//      i. if (!completed):
//           if (restart) → continue (same level)
//           else → break (back to menu)
//      j. Save high score: HighScoreManager::saveHighScore(...)
//      k. Show level complete / game won screens
//      l. ++i;
// ────────────────────────────────────────────
void handlePlay(Level *levels[], int levelCount, int startLevel,
                const std::string &highScoreFile) {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 3d — handleSettings
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Print current settings
//   2. Ask user what to change (e.g., "Color palette (0-3): ")
//   3. Read input and store
//   4. Print "Settings updated."
//   NOTE: Keep this simple. Settings can be stored as static
//         variables or passed through. Don't overcomplicate.
// ────────────────────────────────────────────
void handleSettings() {
  // TODO: implement
}

} // namespace Menu
