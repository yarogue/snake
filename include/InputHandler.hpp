#pragma once
#include "Direction.hpp"
#include <optional>

struct InputHandler {
    std::optional<Direction> pollInput(int key) const;
    bool isQuitKey(int key) const;
};
