#include "Board.hpp"
#include "Position.hpp"
#include <cstdlib>

Position Board::wrap(Position pos) const {
  return Position{(pos.x % width + width) % width,
                  (pos.y % height + height) % height};
}

bool Board::isObstacle(Position pos) const {
  for (const Obstacle &obs : obstacles) {
    if (obs.position == pos) {
      return true;
    }
  }
  return false;
}

void Board::generateObstacles(int count,
                              const std::vector<Position> &forbidden) {
  obstacles.clear();
  while (obstacles.size() < count) {
    Position candidate{rand() % width, rand() % height};
    bool isForbidden = false;
    for (const Position &pos : forbidden) {
      if (pos == candidate) {
        isForbidden = true;
        break;
      }
    }
    if (isForbidden)
      continue;
    bool isDuplicate = false;
    for (const Obstacle &obs : obstacles) {
      if (obs.position == candidate) {
        isDuplicate = true;
        break;
      }
    }
    if (isDuplicate)
      continue;
    obstacles.push_back(Obstacle{candidate});
  }
}

Board Board::create(int width, int height) {
  Board board;
  board.width = width;
  board.height = height;
  board.obstacles = {};
  return board;
}