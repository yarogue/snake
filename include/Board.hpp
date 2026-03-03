#pragma once
#include "Position.hpp"
#include "Obstacle.hpp"
#include <vector>

struct Board {

  //Members:

  int width;          // number of columns
  int height;         // number of rows
  std::vector<Obstacle> obstacles;

  //Methods

  Position wrap(Position pos) const;

  bool isObstacle(Position pos) const;

  void generateObstacles(int count, const std::vector<Position>& forbidden);

  static Board create(int width, int height);

};
