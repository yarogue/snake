#pragma once
// #include "Direction.hpp"
// #include <optional>

// ============================================================
// TODO 4a — InputHandler struct  (header)
// ============================================================
// InputHandler reads keyboard input and translates raw key codes
// into game Directions.
//
// WHY non-blocking?
//   The game loop ticks at a fixed interval. We can't wait forever
//   for a keypress — if no key was pressed, we just proceed.
//   ncurses timeout() makes getch() return ERR immediately if no
//   key is available. We set this in Renderer::init() or here.
//
// MEMBERS:
//   (none needed for now — all methods are stateless)
//
// METHODS to declare (implement in InputHandler.cpp):
//
//   std::optional<Direction> pollInput() const
//     → Call getch() from ncurses (non-blocking because of timeout).
//     → If the return is ERR (no key pressed) → return std::nullopt
//     → Map key codes to Directions:
//         KEY_UP    → Direction::UP
//         KEY_DOWN  → Direction::DOWN
//         KEY_LEFT  → Direction::LEFT
//         KEY_RIGHT → Direction::RIGHT
//         'w', 'W'  → Direction::UP      (WASD alternative)
//         's', 'S'  → Direction::DOWN
//         'a', 'A'  → Direction::LEFT
//         'd', 'D'  → Direction::RIGHT
//     → For any other key → return std::nullopt
//
//   bool isQuitKey(int key) const
//     → Return true if key == 'q' or key == 'Q'
//     → Used in the game loop to let the player exit cleanly.
//
// HINT on std::optional:
//   std::optional<T> is a type that either holds a T value or is empty.
//   Return std::nullopt when there is nothing to return.
//   Check with:  if (auto dir = handler.pollInput()) { ... }
// ============================================================

struct InputHandler {
  // TODO 4a-1: declare method signatures listed above
};
