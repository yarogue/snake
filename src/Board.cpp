#include "Board.hpp"
#include "Position.hpp"
#include <cstdlib>

Position Board::wrap(Position pos) const {
  return Position{(pos.x % width + width) % width,
                  (pos.y % height + height) % height};
}

bool Board::isObstacle(Position pos) const {
  for (const Obstacle &obs : obstacles) {
    for (const Position &cell : obs.cells) {
      if (cell == pos)
        return true;
    }
  }
  return false;
}

void Board::generateObstacles(int count,
                              const std::vector<Position> &forbidden) {
  obstacles.clear();
  auto shapes = ObstacleShapes::allShapes();

  int placed = 0;
  int attempts = 0;
  while (placed < count && attempts < count * 20) {
    attempts++;

    // Pick random anchor position
    Position anchor{rand() % width, rand() % height};

    // Pick random shape
    auto &shape = shapes[rand() % shapes.size()];

    // Build the actual cells from anchor + offsets
    std::vector<Position> cells;
    bool valid = true;
    for (const Position &offset : shape) {
      Position cell{anchor.x + offset.x, anchor.y + offset.y};

      // Check within bounds
      if (cell.x < 0 || cell.x >= width || cell.y < 0 || cell.y >= height) {
        valid = false;
        break;
      }

      // Check not forbidden (snake body)
      for (const Position &f : forbidden) {
        if (f == cell) {
          valid = false;
          break;
        }
      }
      if (!valid)
        break;

      // Check not overlapping existing obstacles
      if (isObstacle(cell)) {
        valid = false;
        break;
      }

      cells.push_back(cell);
    }

    if (valid) {
      obstacles.push_back(Obstacle{cells});
      placed++;
    }
  }
}

Board Board::create(int width, int height) {
  Board board;
  board.width = width;
  board.height = height;
  board.obstacles = {};
  return board;
}