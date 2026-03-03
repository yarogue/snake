#include "include/Snake.hpp"

#include "../include/Position.hpp"
#include "../include/Direction.hpp"

// ============================================================
// TODO 1c — Snake struct  (implementation)
// ============================================================
// Implement each method declared in Snake.hpp.
// The pseudocode below describes what each method should do.
// ============================================================

// --- Snake::move() ---
// TODO 1c-3:
//   1. Compute newHead = getHead() + DirectionUtils::toOffset(currentDirection)
//   2. Push newHead to the FRONT of body  (body.push_front)
//   3. Remove the LAST element of body    (body.pop_back)

void Snake::Move() {
    Position newHead = getHead() +
    DirectionUtils::toOffset(currentDirection);
}

// --- Snake::grow() ---
// TODO 1c-4:
//   1. Same as move() but SKIP step 3 (don't pop the tail)
//   That's it — body grows by one cell.

// --- Snake::getHead() ---
// TODO 1c-5:
//   return body.front()

// --- Snake::isCollidingWithSelf() ---
// TODO 1c-6:
//   head = getHead()
//   Loop through body starting from index 1 (skip the head itself)
//   If any element equals head → return true
//   If loop finishes → return false

// --- Snake::setDirection() ---
// TODO 1c-7:
//   Forbidden pairs (don't allow 180-degree reversal):
//     UP    ↔ DOWN
//     LEFT  ↔ RIGHT
//   If newDir is NOT the opposite of currentDirection → update it
//   Otherwise → do nothing (ignore the input)

// --- Snake::create() (static factory) ---
// TODO 1c-8:
//   snake.currentDirection = startDir
//   oppositeOffset = -1 * DirectionUtils::toOffset(startDir)
//     (multiply both x and y by -1)
//   Loop initialLength times:
//     push Position{ startPos + (i * oppositeOffset) } into snake.body
//   return snake
