#include "InputHandler.hpp"
#include "raylib.h"

std::optional<Direction> InputHandler::pollInput() const {
    if (IsKeyPressed(KEY_UP)    || IsKeyPressed(KEY_W)) return Direction::UP;
    if (IsKeyPressed(KEY_DOWN)  || IsKeyPressed(KEY_S)) return Direction::DOWN;
    if (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A)) return Direction::LEFT;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) return Direction::RIGHT;
    return std::nullopt;
}

bool InputHandler::isQuitKey() const {
    return IsKeyPressed(KEY_Q);
}

bool InputHandler::isPauseKey() const {
    return IsKeyPressed(KEY_P);
}
