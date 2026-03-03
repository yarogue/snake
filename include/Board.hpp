#pragma once
// #include "Position.hpp"
// #include "Obstacle.hpp"
// #include <vector>

// ============================================================
// TODO 1d — Board struct  (header)
// ============================================================
// The Board owns the grid dimensions and the list of obstacles.
// It also handles the TOROIDAL wrap logic.
//
// MEMBERS:
//   int width;          // number of columns
//   int height;         // number of rows
//   std::vector<Obstacle> obstacles;
//
// METHODS to declare here (implement in Board.cpp):
//
//   Position wrap(Position pos) const
//     → Toroidal grid: if pos goes off an edge, it reappears
//       on the opposite side.
//       HINT:
//         x = (pos.x % width + width) % width   ← handles negatives too
//         y = (pos.y % height + height) % height
//       Return the corrected Position.
//
//   bool isObstacle(Position pos) const
//     → Search the obstacles list. Return true if any obstacle
//       occupies the given position.
//
//   void generateObstacles(int count, const std::vector<Position>& forbidden)
//     → Randomly place `count` obstacles on the board.
//       The `forbidden` list contains positions that must stay clear
//       (e.g., where the snake starts, where food should appear).
//       HINT: use rand() % width and rand() % height, then check
//             forbidden list before adding.
//
//   static Board create(int width, int height)
//     → Simple factory: return a Board with given dimensions
//       and an empty obstacles list.
// ============================================================

struct Board {
  // TODO 1d-1: declare width, height, obstacles

  // TODO 1d-2: declare method signatures listed above
};
