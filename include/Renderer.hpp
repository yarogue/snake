#pragma once
// #include "IRenderable.hpp"
// #include "Board.hpp"
// #include "Snake.hpp"
// #include <string>

// ============================================================
// TODO 3a — Renderer struct  (header)
// ============================================================
// The Renderer is responsible for drawing EVERYTHING to the terminal.
// It talks to the terminal directly using ncurses (or ANSI codes).
//
// We use ncurses for clean terminal drawing.
// Key ncurses functions you will need:
//   initscr()       → start ncurses mode
//   cbreak()        → disable line buffering (read keys immediately)
//   noecho()        → don't print typed keys to screen
//   keypad(stdscr, TRUE) → enable arrow keys
//   timeout(ms)     → set non-blocking input timeout
//   clear()         → clear the screen buffer
//   mvprintw(y,x, "text") → print text at row y, col x
//   refresh()       → push buffer to actual screen
//   endwin()        → shut down ncurses (call before exit)
//
// MEMBERS:
//   int offsetX;   // left padding so board is centered (optional)
//   int offsetY;   // top padding
//
// METHODS to declare (implement in Renderer.cpp):
//
//   void init()
//     → Call ncurses startup functions listed above.
//
//   void shutdown()
//     → Call endwin()
//
//   void drawBoard(const Board& board) const
//     → Draw the border walls around the board.
//     → Draw each obstacle as '#' at its position.
//
//   void drawSnake(const Snake& snake) const
//     → Draw snake HEAD as '@' or 'O'
//     → Draw snake BODY segments as 'o' or '*'
//
//   void drawFood(Position foodPos) const
//     → Draw food as '$' or '*' at foodPos
//
//   void drawHUD(int score, int level) const
//     → Draw score and level number at top or bottom of screen.
//     → e.g.  "Score: 42   Level: 2"
//
//   void drawGameOver() const
//     → Print a centered "GAME OVER" message and wait for input.
// ============================================================

struct Renderer {
  // TODO 3a-1: declare offsetX, offsetY

  // TODO 3a-2: declare method signatures listed above
};
