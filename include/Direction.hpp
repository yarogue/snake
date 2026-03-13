#pragma once
#include <iostream>
#include <ostream>

#include "Position.hpp"

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

namespace DirectionUtils {
    inline Position toOffset(Direction dir) {
        switch (dir) {
            case Direction::UP:    return Position{ 0, -1};
            case Direction::DOWN:  return Position{ 0, +1};
            case Direction::LEFT:  return Position{-1,  0};
            case Direction::RIGHT: return Position{+1,  0};
            default:               return Position{ 0,  0};
        }
    }
}