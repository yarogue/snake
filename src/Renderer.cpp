#include "Renderer.hpp"
#include <ncurses.h>

void Renderer::init() {
  initscr();            // start ncurses mode
  cbreak();             // read keys immediately (no Enter needed)
  noecho();             // don't print typed keys on screen
  keypad(stdscr, TRUE); // enable arrow key support
  curs_set(0);          // hide the blinking cursor

  // TODO: Set timeout later when GameEngine knows the tick speed
}

void Renderer::shutdown() { endwin(); }

void Renderer::drawBoard(const Board &board) const {

  clear();

  //   Drawing borders:
  for (int x = 0; x <= board.width + 1; ++x) {
    mvprintw(offsetY, offsetX + x, "-");                    // top border
    mvprintw(offsetY + board.height + 1, offsetX + x, "-"); // bottom border
  }

  for (int y = 0; y <= board.height + 1; ++y) {
    mvprintw(offsetY + y, offsetX, "|");                   // left border
    mvprintw(offsetY + y, offsetX + board.width + 1, "|"); // right border
  }

  //   Draw corners:

  mvprintw(offsetY, offsetX, "+"); // top-left corner

  mvprintw(offsetY, offsetX + board.width + 1, "+"); // top-right corner

  mvprintw(offsetY + board.height + 1, offsetX, "+"); // bottom-left corner

  mvprintw(offsetY + board.height + 1, // bottom-right corner
           offsetX + board.width + 1, "+");
}

void Renderer::drawSnake(const Snake &snake) const {
  Position head = snake.getHead();
  mvprintw(offsetY + 1 + head.y, offsetX + 1 + head.x, "@");

  for (size_t i = 1; i < snake.body.size(); ++i) {
    mvprintw(offsetY + 1 + snake.body[i].y, offsetX + 1 + snake.body[i].x, "o");
  }
}

void Renderer::drawFood(Position foodPos) const {
  mvprintw(offsetY + 1 + foodPos.y, offsetX + 1 + foodPos.x, "$");
}

void Renderer::drawHUD(int score, int level) const {
  mvprintw(0, 0, "Score: %d   Level: %d", score, level);
  refresh();
}

void Renderer::drawGameOver(const Board &board) const {
  mvprintw(board.height / 2, board.width / 2 - 5, "GAME OVER");
  mvprintw(board.height / 2 + 1, board.width / 2 - 8, "Press any key to exit");
  refresh();
  getch();
}