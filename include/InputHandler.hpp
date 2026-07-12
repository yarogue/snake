#pragma once
#include "Direction.hpp"
#include <optional>

struct InputHandler {
    std::optional<Direction> pollInput() const;
    bool isQuitKey() const;
    bool isPauseKey() const;
};
