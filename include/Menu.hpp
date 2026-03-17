#pragma once
#include "Level.hpp"
#include <string>

namespace Menu {

void showMenu();
void menuLoop(Level *levels[], int levelCount,
              const std::string &highScoreFile);
void handlePlay(Level *levels[], int levelCount, int startLevel,
                const std::string &highScoreFile);
void handleSettings();

} // namespace Menu
