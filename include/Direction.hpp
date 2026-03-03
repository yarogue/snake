#pragma once
#include <iostream>
#include <ostream>

#include "Position.hpp"

// ============================================================
// TODO 1b — Direction enum + DirectionUtils namespace
// ============================================================
// Direction represents the 4 possible movement directions of the snake.
//
// STEP 1: Define an enum class with 4 values:
//   enum class Direction { UP, DOWN, LEFT, RIGHT };
//
//   Use `enum class` (not plain `enum`) — it is scoped and type-safe.
//   You access values as Direction::UP, Direction::DOWN, etc.
//
// STEP 2: Create a namespace called DirectionUtils.
//   Inside it, write ONE function:
//
//   Position toOffset(Direction dir)
//   → converts a Direction into a Position that represents
//     how much to move per step.
//     Examples:
//       UP    → Position{  0, -1 }   (row decreases going up)
//       DOWN  → Position{  0, +1 }
//       LEFT  → Position{ -1,  0 }
//       RIGHT → Position{ +1,  0 }
//
//   Use an if/else or switch statement.
//
// WHY a namespace instead of a free function?
//   The spec says "no global functions". A namespace groups
//   related utilities cleanly without exposing them globally.
//
// ============================================================
// #include "Position.hpp"   ← uncomment when you add Position.hpp

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

namespace DirectionUtils {
    inline Position toOffset(Direction dir) {
        switch (dir) {
            case Direction::UP:    return Position{ 0, -1};
            case Direction::DOWN:  return Position{ 0, +1};
            case Direction::LEFT:  return Position{-1,  0};
            case Direction::RIGHT: return Position{+1,  0};
            default:               return Position{ 0,  0};
        }
    }
}