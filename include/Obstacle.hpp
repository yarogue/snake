#pragma once
#include "Position.hpp"

struct Obstacle {

  //Members
  Position position;

  // FUTURE EXTENSION NOTE:
  //   When we add difficulty scaling, obstacles may come in SHAPES
  //   (e.g., L-shaped rocks, 2×2 boulders).
  //   We could change `Position position` to
  //   `std::vector<Position> cells` later — keep that in mind.

};
