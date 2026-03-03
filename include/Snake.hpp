#pragma once
#include "Position.hpp"
#include "Direction.hpp"
#include <deque>

// ============================================================
// TODO 1c — Snake struct  (header)
// ============================================================
// The Snake owns its body (a sequence of Positions) and its
// current movement direction.
//
// WHY a deque?
//   std::deque lets you efficiently push to the FRONT (new head)
//   and pop from the BACK (old tail) in O(1).
//   That is exactly how a snake moves each tick.
//
// MEMBERS:
//   std::deque<Position> body;
//     → body.front() is always the HEAD
//     → body.back()  is always the TAIL
//
//   Direction currentDirection;
//
// METHODS to declare here (implement in Snake.cpp):
//
//   void move()
//     → Moves the snake one step in currentDirection.
//       Normal move: push new head, pop tail.
//
//   void grow()
//     → Like move(), but do NOT pop the tail.
//       Call this instead of move() when the snake eats food.
//
//   Position getHead() const
//     → Return body.front()
//
//   bool isCollidingWithSelf() const
//     → Check if the head position appears anywhere else in body.
//       HINT: search body[1..end] for a position equal to getHead()
//
//   void setDirection(Direction newDir)
//     → Set currentDirection = newDir, BUT prevent 180-degree turns.
//       (e.g., if moving RIGHT, ignore a LEFT input)
//       HINT: use DirectionUtils::toOffset and compare offsets,
//             or just check forbidden pairs explicitly.
//
//   static Snake create(Position startPos, Direction startDir, int
//   initialLength)
//     → A static factory function that builds a valid Snake.
//       Fill the body with `initialLength` cells going BACKWARD
//       from startPos in the opposite direction of startDir.
//       Return the ready Snake.
// ============================================================

struct Snake {

  //Member variables
  std::deque<Position> body;
  Direction currentDirection;

  //Member functions declarations
  void Move();
  void Grow();
  Position getHead() const;
  bool isCollidingWithSelf() const;
  void setDirection(Direction newDir);

  //Static factory function
  static Snake create(Position   startPosition,
                      Direction  startDirection,
                      int        initialLength);
};