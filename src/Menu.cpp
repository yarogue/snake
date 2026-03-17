#include "Menu.hpp"
#include "GameEngine.hpp"
#include "HighScoreManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace Menu {

    void showMenu() {
        std::cout << "╔══════════════════════════════════════╗\n";
        std::cout << "║        SNAKE+WORD PUZZLE GAME        ║\n";
        std::cout << "╠══════════════════════════════════════╣\n";
        std::cout << "║ Commands:                            ║\n";
        std::cout << "║ [1-3]       - Play a level 1 ,2 or 3 ║\n";
        std::cout << "║ [h]         - Show high scores       ║\n";
        std::cout << "║ [s]         - Change game settings   ║\n";
        std::cout << "║ [q]         - Exit the game          ║\n";
        std::cout << "╚══════════════════════════════════════╝\n";
    }

void menuLoop(Level *levels[], int levelCount,
              const std::string &highScoreFile) {
    std::string input;
    bool isRunning = true;
    while (isRunning) {
        showMenu();
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") {
            isRunning = false;
            break;
        }else if (input == "h" || input == "H") {
            HighScoreManager::printHighScores(highScoreFile);
        }else if (input == "s" || input == "S") {
            std::cout << "settings" << std::endl;
            handleSettings();
        }else if (input == "1" || input == "2" || input == "3") {
            const int levelNum = std::stoi(input);
            std::cout << "Starting level " << levelNum << "...\n";
            handlePlay(levels, levelCount, levelNum - 1, highScoreFile);
        }else {
            std::cout << "Invalid input" << std::endl;
        }
    }
}


    void handlePlay(Level *levels[], const int levelCount, const int startLevel,
                            const std::string &highScoreFile) {
    int carryPuzzles = 0;
    for (int i = startLevel; i < levelCount;) {
        auto engine = new GameEngine;
        *engine = GameEngine::create(*levels[i]);
        engine->puzzlesSolved = carryPuzzles;
        engine->puzzlesStartCount = carryPuzzles;
        engine->run();
        carryPuzzles = engine->puzzlesSolved;
        bool isCompleted = engine->checkLevelComplete();
        bool restart = engine->wantsRestart();
        int score = engine->score;
        delete engine;
        // Save score
        HighScoreManager::saveHighScore(highScoreFile,
            levels[i]->levelNumber, score, carryPuzzles);
        if (!isCompleted) {
            if (restart) {
                continue;    // replay same level
            } else {
                break;       // back to menu
            }
        }
        i++;  // next level
    }
}

    void handleSettings() {
    std::cout << "\n=== SETTINGS ===\n";
    std::cout << "Color palette (0-3): ";

    std::string input;
    std::getline(std::cin, input);

    int palette = std::stoi(input);
    if (palette >= 0 && palette <= 3) {
        // Store as a static variable that GameEngine can access
        std::cout << "Palette set to " << palette << "\n";
    } else {
        std::cout << "Invalid palette. Use 0-3.\n";
    }
}

} // namespace Menu
