// #include "Board.hpp"
// #include "Position.hpp"

// ============================================================
// TODO 1d — Board struct  (implementation)
// ============================================================

// --- Board::wrap() ---
// TODO 1d-3:
//   result.x = (pos.x % width + width) % width
//   result.y = (pos.y % height + height) % height
//   return result
//   NOTE: the double-modulo pattern handles negative values correctly.
//         e.g. (-1 % 10 + 10) % 10 = 9  ✓

// --- Board::isObstacle() ---
// TODO 1d-4:
//   Loop through all obstacles
//   For each obstacle, check if its position equals pos
//   If yes → return true
//   After loop → return false

// --- Board::generateObstacles() ---
// TODO 1d-5:
//   Clear the current obstacles list first
//   Repeat until obstacles.size() == count:
//     candidate = Position{ rand() % width, rand() % height }
//     Check candidate is NOT in the forbidden list
//     Check candidate is NOT already an obstacle (no duplicates)
//     If clear → add Obstacle{ candidate } to obstacles

// --- Board::create() ---
// TODO 1d-6:
//   Board b
//   b.width  = width
//   b.height = height
//   b.obstacles = {} (empty)
//   return b
