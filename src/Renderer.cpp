// #include "Renderer.hpp"
// #include <ncurses.h>

// ============================================================
// TODO 3b — Renderer::init() and Renderer::shutdown()
// ============================================================

// --- Renderer::init() ---
// TODO 3b-1:
//   Call initscr()
//   Call cbreak()         → get keystrokes immediately, no Enter needed
//   Call noecho()         → don't echo typed characters
//   Call keypad(stdscr, TRUE)  → enable arrow key support
//   Call curs_set(0)      → hide the cursor (cleaner look)
//   Set timeout later when GameEngine knows the tick speed
//   (or call timeout(tickMs) here if passed as parameter)

// --- Renderer::shutdown() ---
// TODO 3b-2:
//   Call endwin()
//   That's it — ncurses cleans up the rest.

// ============================================================
// TODO 3c — Renderer::drawBoard()
// ============================================================
// TODO 3c-1:
//   Call clear() to wipe the previous frame
//
//   Draw top border:
//     Loop x from 0 to board.width+1
//     mvprintw(offsetY, offsetX + x, "-")
//
//   Draw bottom border:
//     Loop x from 0 to board.width+1
//     mvprintw(offsetY + board.height + 1, offsetX + x, "-")
//
//   Draw left and right borders:
//     Loop y from 0 to board.height+1
//     mvprintw(offsetY + y, offsetX, "|")
//     mvprintw(offsetY + y, offsetX + board.width + 1, "|")
//
//   Draw corners:
//     mvprintw(offsetY, offsetX, "+")
//     (do all 4 corners)
//
//   Draw each obstacle:
//     For each obs in board.obstacles:
//       mvprintw(offsetY + 1 + obs.position.y,
//                offsetX + 1 + obs.position.x, "#")

// ============================================================
// TODO 3d — Renderer::drawSnake(), drawFood(), drawHUD(), drawGameOver()
// ============================================================

// --- drawSnake() ---
// TODO 3d-1:
//   Draw head: mvprintw(y, x, "@")   (use snake.getHead())
//   Loop through body from index 1 onward:
//     Draw each segment: mvprintw(y, x, "o")
//   Remember to add offsetY+1 and offsetX+1 to all coordinates!

// --- drawFood() ---
// TODO 3d-2:
//   mvprintw(offsetY + 1 + foodPos.y, offsetX + 1 + foodPos.x, "$")

// --- drawHUD() ---
// TODO 3d-3:
//   mvprintw(0, 0, "Score: %d   Level: %d", score, level)
//   Call refresh() HERE (only once per frame, after all drawing is done)

// --- drawGameOver() ---
// TODO 3d-4:
//   mvprintw(board.height/2, board.width/2 - 5, "GAME OVER")
//   mvprintw(board.height/2 + 1, board.width/2 - 8, "Press any key to exit")
//   refresh()
//   Call getch() to wait for a keypress before exiting
