#pragma once
// #include "Position.hpp"

// ============================================================
// TODO 1e — Obstacle struct
// ============================================================
// Obstacles are static "stones" on the board that kill the snake
// if it runs into them. Simple to start: just a position.
// Later (Phase word-game extension) we might add more properties.
//
// MEMBERS:
//   Position position;
//
// No methods needed for now — Board handles collision detection.
//
// FUTURE EXTENSION NOTE:
//   When we add difficulty scaling, obstacles may come in SHAPES
//   (e.g., L-shaped rocks, 2×2 boulders).
//   You could change `Position position` to
//   `std::vector<Position> cells` later — keep that in mind.
// ============================================================

struct Obstacle {
  // TODO 1e-1: declare Position position
};
