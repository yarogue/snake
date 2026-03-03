// #include "InputHandler.hpp"
// #include <ncurses.h>

// ============================================================
// TODO 4b — InputHandler implementation
// ============================================================

// --- InputHandler::pollInput() ---
// TODO 4b-1:
//   int key = getch()   ← ncurses non-blocking read (needs timeout set)
//   if key == ERR → return std::nullopt
//   if key == KEY_UP    or key == 'w' or key == 'W' → return Direction::UP
//   if key == KEY_DOWN  or key == 's' or key == 'S' → return Direction::DOWN
//   if key == KEY_LEFT  or key == 'a' or key == 'A' → return Direction::LEFT
//   if key == KEY_RIGHT or key == 'd' or key == 'D' → return Direction::RIGHT
//   default → return std::nullopt

// --- InputHandler::isQuitKey() ---
// TODO 4b-2:
//   return (key == 'q' || key == 'Q')
