#include "GameEngine.hpp"
#include "Level.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  srand(time(nullptr));

  // ---- EASY puzzles (short words) ----
  std::vector<std::pair<std::string, std::string>> easyPuzzles = {
      {"WIZARD", "Man with magical powers"},
      {"KING",
       "The man who reigns on England and the knight has the duty to protect"},
      {"SWORD", "Weapon the knight uses to defend himself"},
      {"BRIDGE", "Where we can walk over rivers without getting wet"},
      {"HORSE", "An animal the knight travels on"},
      {"RIVER", "Where water runs"},
      {"LADY", "Woman of high society"},
      {"ARMOUR", "Serves to protect the knight in battles"},
      {"CASTLE", "The house of kings, ladies and knights"},
      {"SADDLE", "Where the knight sits on the horse"},
  };

  // ---- MEDIUM puzzles (longer words) ----
  std::vector<std::pair<std::string, std::string>> mediumPuzzles = {
      {"VILLAGER", "A person who lives in a small town or rural community"},
      {"KNIGHTHOOD", "The code of conduct and qualities of an ideal knight"},
      {"MINSTREL", "A medieval singer or musician who tells stories"},
      {"PRISONER", "Someone kept in a dungeon against their will"},
      {"DRAGON", "A mythical fire-breathing beast"},
      {"FORTRESS", "A heavily protected building or strategic post"},
      {"CHAINMAIL", "Flexible armor made of interlinked metal rings"},
      {"COURTYARD", "An open area inside the castle walls"},
      {"BANQUET", "A large, formal feast with lots of food"},
      {"TOURNAMENT", "A sporting competition where knights practice fighting"},
      {"GUARDIAN", "Someone who protects a person or a place"},
      {"CHARIOT", "A vehicle with two wheels pulled by horses"},
      {"MESSENGER", "A person who carries news from one kingdom to another"},
      {"KINGDOM", "The entire land and people ruled by a King"},
      {"SHIELD", "A protective tool held in the hand to block attacks"},
  };

  // ---- HARD puzzles (complex words) ----
  std::vector<std::pair<std::string, std::string>> hardPuzzles = {
      {"SOVEREIGN", "A supreme ruler, especially a monarch"},
      {"TYRANNY", "Use of force or power to rule in a cruel way"},
      {"MANUSCRIPT", "An original text written by hand"},
      {"CHANCELLOR", "A high-ranking official or a senior judge"},
      {"EXECUTION", "The carrying out of a death sentence"},
      {"BATTLEMENT",
       "The jagged gaps at the top of a castle wall for firing arrows"},
      {"INHERITANCE", "Money or titles passed down when someone dies"},
      {"AMBASSADOR", "A diplomat sent as a representative to another land"},
      {"TREACHERY", "Betrayal of one's country or king"},
      {"PROPHECY", "A prediction of what will happen in the future"},
      {"CATAPULT", "A machine used to throw heavy stones at walls"},
      {"ARCHERY", "The practice of using a bow and arrow"},
      {"MONASTERY", "A building where monks live and work"},
      {"LEGENDARY", "Someone famous for many generations"},
      {"PROCLAMATION", "A formal public announcement"},
      {"CONQUEROR", "A person who takes control of a land by force"},
      {"ALCHEMIST", "An ancient scientist who studied magic and chemistry"},
      {"DRAWBRIDGE", "A gate that can be raised or lowered to cross a moat"},
      {"CONSULTATION", "A formal meeting for discussion or advice"},
      {"SUCCESSION", "The process of inheriting a title or office"},
  };

  // Define 3 levels with increasing difficulty
  Level levels[3];

  // Level 1 — Easy
  levels[0].levelNumber = 1;
  levels[0].boardWidth = 50;
  levels[0].boardHeight = 20;
  levels[0].obstacleCount = 3;
  levels[0].initialSnakeLen = 3;
  levels[0].tickIntervalMs = 200;
  levels[0].puzzlesToSolve = 3;
  levels[0].puzzles = easyPuzzles;

  // Level 2 — Medium
  levels[1].levelNumber = 2;
  levels[1].boardWidth = 50;
  levels[1].boardHeight = 20;
  levels[1].obstacleCount = 8;
  levels[1].initialSnakeLen = 3;
  levels[1].tickIntervalMs = 150;
  levels[1].puzzlesToSolve = 4;
  levels[1].puzzles = mediumPuzzles;

  // Level 3 — Hard
  levels[2].levelNumber = 3;
  levels[2].boardWidth = 50;
  levels[2].boardHeight = 20;
  levels[2].obstacleCount = 14;
  levels[2].initialSnakeLen = 3;
  levels[2].tickIntervalMs = 100;
  levels[2].puzzlesToSolve = 5;
  levels[2].puzzles = hardPuzzles;

  // Level selection menu
  std::cout << "=== SNAKE WORD GAME ===" << std::endl;
  std::cout << "  1. Easy   (3 puzzles, slow)" << std::endl;
  std::cout << "  2. Medium (4 puzzles, faster)" << std::endl;
  std::cout << "  3. Hard   (5 puzzles, fast)" << std::endl;
  std::cout << "Enter choice (1-3): ";

  int choice;
  std::cin >> choice;
  if (choice < 1 || choice > 3)
    choice = 1;
  int startLevel = choice - 1; // convert to 0-indexed

  // Level progression loop (from chosen level onward)
  int carryPuzzles = 0; // running total across levels

  for (int i = startLevel; i < 3;) {
    GameEngine engine = GameEngine::create(levels[i]);
    engine.puzzlesSolved = carryPuzzles;     // carry from previous levels
    engine.puzzlesStartCount = carryPuzzles; // baseline for this level
    engine.run();
    carryPuzzles = engine.puzzlesSolved; // save running total

    // If player died (didn't complete level)
    if (!engine.checkLevelComplete()) {
      if (engine.wantsRestart()) {
        continue; // Restart same level
      } else {
        break; // Quit
      }
    }

    // Show level complete screen
    engine.renderer.drawLevelComplete(engine.board, levels[i].levelNumber);

    // After level 3, show win screen
    if (i == 2) {
      engine.renderer.drawGameWon(engine.board);
    }

    ++i; // Advance to next level
  }

  return 0;
}