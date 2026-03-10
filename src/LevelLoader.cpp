#include "LevelLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

// ============================================================
// TODO Phase 1 — LevelLoader (implementation)
// ============================================================
// Implement the three functions declared in LevelLoader.hpp.
// Read the header file TODOs for detailed pseudocode.
// ============================================================

namespace LevelLoader {

// ────────────────────────────────────────────
// TODO 1a — loadLevel
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Open file with std::ifstream
//   2. If open fails → print error → return nullptr
//   3. Allocate: Level* level = new Level;
//   4. Read lines in a loop:
//      a. If line is empty → skip
//      b. If line is "[puzzles]" → switch to puzzle-reading mode
//      c. In config mode:
//         - Find '=' position
//         - Extract key (before '=') and value (after '=')
//         - Match key to level fields:
//           "levelNumber"   → level->levelNumber = stoi(value)
//           "boardWidth"    → level->boardWidth = stoi(value)
//           "boardHeight"   → level->boardHeight = stoi(value)
//           "obstacleCount" → level->obstacleCount = stoi(value)
//           "initialSnakeLen" → level->initialSnakeLen = stoi(value)
//           "tickIntervalMs"  → level->tickIntervalMs = stoi(value)
//           "puzzlesToSolve"  → level->puzzlesToSolve = stoi(value)
//      d. In puzzle mode:
//         - Find '|' position
//         - Extract word (before '|') and hint (after '|')
//         - Push {word, hint} pair into level->puzzles
//   5. Close file
//   6. Return level
// ────────────────────────────────────────────
Level *loadLevel(const std::string &filename) {
  // TODO: implement
  return nullptr;
}

// ────────────────────────────────────────────
// TODO 1b — validateLevel
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. If level is nullptr → print "null level" → return false
//   2. Check each field:
//      - boardWidth > 0       (else print "invalid board width")
//      - boardHeight > 0      (else print "invalid board height")
//      - obstacleCount >= 0   (else print "invalid obstacle count")
//      - initialSnakeLen > 0  (else print "invalid snake length")
//      - tickIntervalMs > 0   (else print "invalid tick interval")
//      - puzzlesToSolve > 0   (else print "need at least 1 puzzle to solve")
//      - puzzles.size() > 0   (else print "no puzzles loaded")
//      - puzzlesToSolve <= puzzles.size()
//        (else print "puzzlesToSolve exceeds available puzzles")
//   3. Return true if ALL checks pass, false on first failure
// ────────────────────────────────────────────
bool validateLevel(const Level *level) {
  // TODO: implement
  return false;
}

// ────────────────────────────────────────────
// TODO 1c — freeLevel
// ────────────────────────────────────────────
// PSEUDOCODE:
//   1. Call: delete level;
//   This pairs with the 'new' in loadLevel().
// ────────────────────────────────────────────
void freeLevel(Level *level) {
  // TODO: implement
}

} // namespace LevelLoader
