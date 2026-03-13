#pragma once
#include "Level.hpp"
#include <string>
#include <fstream>

namespace LevelLoader {

Level *loadLevel(const std::string &filename);
bool validateLevel(const Level *level);
void freeLevel(const Level *level);

} // namespace LevelLoader
