#include "Snake.hpp"

void Snake::move() {
  Position newHead = getHead() + DirectionUtils::toOffset(currentDirection);
  body.pushFront(newHead);
  body.popBack();
}

void Snake::grow() {
  Position newHead = getHead() + DirectionUtils::toOffset(currentDirection);
  body.pushFront(newHead);
}

Position Snake::getHead() const { return body.front(); }

bool Snake::isCollidingWithSelf() const {
  Position head = getHead();
  for (size_t i = 1; i < body.size(); ++i) {
    if (body.at(i) == head) {
      return true;
    }
  }
  return false;
}

void Snake::setDirection(Direction newDir) {
  bool isIllegalTurn = false;

  switch (currentDirection) {
  case Direction::UP:
    if (newDir == Direction::DOWN) {
      isIllegalTurn = true;
    }
    break;
  case Direction::DOWN:
    if (newDir == Direction::UP) {
      isIllegalTurn = true;
    }
    break;
  case Direction::LEFT:
    if (newDir == Direction::RIGHT) {
      isIllegalTurn = true;
    }
    break;
  case Direction::RIGHT:
    if (newDir == Direction::LEFT) {
      isIllegalTurn = true;
    }
    break;
  }
  if (!isIllegalTurn) {
    currentDirection = newDir;
  }
}

Snake Snake::create(Position startPosition, Direction startDirection,
                    int initialLength) {
  Snake snake;

  snake.currentDirection = startDirection;

  Position offset = DirectionUtils::toOffset(startDirection);
  Position oppositeOffset = Position{-offset.x, -offset.y};

  for (int i = initialLength - 1; i >= 0; --i) {
    Position bodyPos = startPosition;
    bodyPos.x += i * oppositeOffset.x;
    bodyPos.y += i * oppositeOffset.y;
    snake.body.pushFront(bodyPos);
  }
  return snake;
}