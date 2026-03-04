#include "InputHandler.hpp"
#include <ncurses.h>

std::optional<Direction> InputHandler::pollInput(int key) const {
    if (key == ERR) return std::nullopt;

    switch (key) {
        case KEY_UP:    case 'w': case 'W': return Direction::UP;
        case KEY_DOWN:  case 's': case 'S': return Direction::DOWN;
        case KEY_LEFT:  case 'a': case 'A': return Direction::LEFT;
        case KEY_RIGHT: case 'd': case 'D': return Direction::RIGHT;
        default: return std::nullopt;
    }
}

bool InputHandler::isQuitKey(int key) const {
    return (key == 'q' || key == 'Q');
}
