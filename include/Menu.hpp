#pragma once
#include "Level.hpp"
#include <string>

// ============================================================
// TODO Phase 3 — Menu (header)
// ============================================================
// The main menu is a text-based command loop that runs BEFORE
// the ncurses game starts. It uses plain std::cout / std::cin.
//
// WHY text-based?
//   The assessment says: "While inside the menu, the
//   customConsole can be turned off, and interacting with
//   the menu can follow the same flow as calling commands
//   in the zork example solution code."
//   So we use simple std::cout prompts and std::cin input.
//
// MENU DISPLAY:
//   ===========================
//     SNAKE WORD PUZZLE GAME
//   ===========================
//   Commands:
//     play [1-3]   - Play a level
//     highscores   - Show high scores
//     settings     - Change game settings
//     quit         - Exit the game
//   >
//
// FUNCTIONS to implement (in Menu.cpp):
//
//   void showMenu()
//     → Print the menu text shown above using std::cout.
//
//   void menuLoop(Level* levels[], int levelCount,
//                 const std::string& highScoreFile)
//     → Main loop:
//       1. Call showMenu()
//       2. Read input line with std::getline(std::cin, input)
//       3. Parse the command:
//          - "play" or "play 1" → extract level number
//            → call handlePlay(levels, levelCount, startLevel, highScoreFile)
//          - "highscores" → call HighScoreManager::printHighScores(highScoreFile)
//          - "settings"   → call handleSettings()
//          - "quit"       → break out of loop
//          - anything else → print "Unknown command."
//       4. Repeat until "quit"
//
//   void handlePlay(Level* levels[], int levelCount,
//                   int startLevel, const std::string& highScoreFile)
//     → This contains the level progression loop currently in main.cpp.
//     → Create GameEngine with new, run it, delete after.
//     → After each level, save high score.
//     → On death: R to restart current level, Q to return to menu.
//
//   void handleSettings()
//     → Show current settings (e.g., starting color palette).
//     → Let user change them.
//     → Keep it simple — just a color palette choice for now.
// ============================================================

namespace Menu {

void showMenu();
void menuLoop(Level *levels[], int levelCount,
              const std::string &highScoreFile);
void handlePlay(Level *levels[], int levelCount, int startLevel,
                const std::string &highScoreFile);
void handleSettings();

} // namespace Menu
