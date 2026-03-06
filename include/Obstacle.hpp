#pragma once
#include "Position.hpp"
#include <vector>

struct Obstacle {
  std::vector<Position> cells;
};

// Shape factory — returns offset patterns for different obstacle shapes
namespace ObstacleShapes {

// #
inline std::vector<Position> single() { return {{0, 0}}; }

// ###
inline std::vector<Position> hLine() { return {{0, 0}, {1, 0}, {2, 0}}; }

// #
// #
// #
inline std::vector<Position> vLine() { return {{0, 0}, {0, 1}, {0, 2}}; }

// ##
// #
inline std::vector<Position> lShape() { return {{0, 0}, {1, 0}, {0, 1}}; }

// ##
// ##
inline std::vector<Position> square() {
  return {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
}

//  #
// ###
inline std::vector<Position> tShape() {
  return {{1, 0}, {0, 1}, {1, 1}, {2, 1}};
}

// Returns all available shapes
inline std::vector<std::vector<Position>> allShapes() {
  return {single(), hLine(), vLine(), lShape(), square(), tShape()};
}
} // namespace ObstacleShapes
