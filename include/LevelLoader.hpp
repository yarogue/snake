#pragma once
#include "Level.hpp"
#include <string>
#include <fstream>

// ============================================================
// TODO Phase 1 — LevelLoader (header)
// ============================================================
// This module is responsible for reading level data from
// external .txt files and converting them into Level structs.
//
// WHY external files?
//   The assessment requires level data to be stored OUTSIDE
//   the program in separate files. This makes the game
//   "data-driven" — you can change levels without recompiling.
//
// WHY new/delete?
//   The assessment requires correct use of dynamic memory.
//   loadLevel() allocates a Level on the heap with 'new',
//   and the caller must eventually call freeLevel() which
//   uses 'delete' to release that memory.
//
// FILE FORMAT (data/level1.txt):
//   levelNumber=1
//   boardWidth=50
//   boardHeight=20
//   obstacleCount=3
//   initialSnakeLen=3
//   tickIntervalMs=200
//   puzzlesToSolve=3
//
//   [puzzles]
//   WIZARD|Man with magical powers
//   KING|The man who reigns on England...
//
// FUNCTIONS to implement (in LevelLoader.cpp):
//
//   Level* loadLevel(const std::string& filename)
//     → Open the file with std::ifstream.
//     → Read key=value pairs line by line until "[puzzles]".
//       HINT: use line.find('=') to split key and value.
//       Convert value strings to int with std::stoi().
//     → After "[puzzles]", read WORD|HINT pairs.
//       HINT: use line.find('|') to split word and hint.
//     → Allocate a new Level with: Level* level = new Level;
//     → Fill in all fields, push puzzle pairs into level->puzzles.
//     → Return the pointer.
//     → If file cannot be opened, return nullptr.
//
//   bool validateLevel(const Level* level)
//     → Check that the loaded level has valid data:
//       - level is not nullptr
//       - boardWidth > 0 && boardHeight > 0
//       - obstacleCount >= 0
//       - initialSnakeLen > 0
//       - tickIntervalMs > 0
//       - puzzlesToSolve > 0
//       - puzzles vector is not empty
//       - puzzlesToSolve <= puzzles.size()
//     → Return true if all valid, false otherwise.
//     → Print an error message describing what is wrong.
//
//   void freeLevel(Level* level)
//     → Simply call: delete level;
//     → This pairs with the 'new' in loadLevel().
// ============================================================

namespace LevelLoader {

Level *loadLevel(const std::string &filename);
bool validateLevel(const Level *level);
void freeLevel(const Level *level);

} // namespace LevelLoader
