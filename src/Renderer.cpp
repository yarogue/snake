#include "Renderer.hpp"
#include <curses.h>

void Renderer::init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  // Enable colors
  start_color();
  currentPalette = 0;
  applyPalette(0);
}

void Renderer::applyPalette(int paletteIndex) {
  currentPalette = paletteIndex;

  switch (paletteIndex) {
  case 0: // Classic — green snake, white borders
    init_pair(COL_BORDER, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_OBSTACLE, COLOR_RED, COLOR_BLACK);
    init_pair(COL_SNAKE_HEAD, COLOR_GREEN, COLOR_BLACK);
    init_pair(COL_SNAKE_BODY, COLOR_GREEN, COLOR_BLACK);
    init_pair(COL_LETTER_CORRECT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_LETTER_WRONG, COLOR_CYAN, COLOR_BLACK);
    init_pair(COL_HUD, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_PAUSE, COLOR_YELLOW, COLOR_BLACK);
    break;

  case 1: // Ocean — cyan snake, blue obstacles
    init_pair(COL_BORDER, COLOR_BLUE, COLOR_BLACK);
    init_pair(COL_OBSTACLE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COL_SNAKE_HEAD, COLOR_CYAN, COLOR_BLACK);
    init_pair(COL_SNAKE_BODY, COLOR_CYAN, COLOR_BLACK);
    init_pair(COL_LETTER_CORRECT, COLOR_GREEN, COLOR_BLACK);
    init_pair(COL_LETTER_WRONG, COLOR_RED, COLOR_BLACK);
    init_pair(COL_HUD, COLOR_CYAN, COLOR_BLACK);
    init_pair(COL_PAUSE, COLOR_CYAN, COLOR_BLACK);
    break;

  case 2: // Lava — red snake, yellow obstacles
    init_pair(COL_BORDER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_OBSTACLE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_SNAKE_HEAD, COLOR_RED, COLOR_BLACK);
    init_pair(COL_SNAKE_BODY, COLOR_RED, COLOR_BLACK);
    init_pair(COL_LETTER_CORRECT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_LETTER_WRONG, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COL_HUD, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_PAUSE, COLOR_RED, COLOR_BLACK);
    break;

  case 3: // Royal — magenta snake, cyan borders
    init_pair(COL_BORDER, COLOR_CYAN, COLOR_BLACK);
    init_pair(COL_OBSTACLE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_SNAKE_HEAD, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COL_SNAKE_BODY, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COL_LETTER_CORRECT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_LETTER_WRONG, COLOR_RED, COLOR_BLACK);
    init_pair(COL_HUD, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COL_PAUSE, COLOR_MAGENTA, COLOR_BLACK);
    break;
  }
}

void Renderer::nextPalette() { applyPalette((currentPalette + 1) % 4); }

void Renderer::shutdown() { endwin(); }

void Renderer::drawBoard(const Board &board) const {
  clear();

  attron(COLOR_PAIR(COL_BORDER));
  for (int x = 0; x <= board.width + 1; ++x) {
    mvprintw(offsetY, offsetX + x, "-");
    mvprintw(offsetY + board.height + 1, offsetX + x, "-");
  }
  for (int y = 0; y <= board.height + 1; ++y) {
    mvprintw(offsetY + y, offsetX, "|");
    mvprintw(offsetY + y, offsetX + board.width + 1, "|");
  }
  mvprintw(offsetY, offsetX, "+");
  mvprintw(offsetY, offsetX + board.width + 1, "+");
  mvprintw(offsetY + board.height + 1, offsetX, "+");
  mvprintw(offsetY + board.height + 1, offsetX + board.width + 1, "+");
  attroff(COLOR_PAIR(COL_BORDER));

  // Draw obstacles
  attron(COLOR_PAIR(COL_OBSTACLE) | A_BOLD);
  for (const Obstacle &obs : board.obstacles) {
    for (const Position &cell : obs.cells) {
      mvprintw(offsetY + 1 + cell.y, offsetX + 1 + cell.x, "#");
    }
  }
  attroff(COLOR_PAIR(COL_OBSTACLE) | A_BOLD);
}

void Renderer::drawSnake(const Snake &snake) const {
  // Head
  attron(COLOR_PAIR(COL_SNAKE_HEAD) | A_BOLD);
  Position head = snake.getHead();
  mvprintw(offsetY + 1 + head.y, offsetX + 1 + head.x, "@");
  attroff(COLOR_PAIR(COL_SNAKE_HEAD) | A_BOLD);

  // Body
  attron(COLOR_PAIR(COL_SNAKE_BODY));
  for (size_t i = 1; i < snake.body.size(); ++i) {
    mvprintw(offsetY + 1 + snake.body[i].y, offsetX + 1 + snake.body[i].x, "o");
  }
  attroff(COLOR_PAIR(COL_SNAKE_BODY));
}

void Renderer::drawLetters(const std::vector<LetterPickup> &letters,
                           const WordPuzzle &puzzle) const {
  auto missing = puzzle.getMissingLetters();

  for (const LetterPickup &lp : letters) {
    bool isCorrect = missing.count(lp.letter) > 0;
    int col = isCorrect ? COL_LETTER_CORRECT : COL_LETTER_WRONG;

    attron(COLOR_PAIR(col) | (isCorrect ? A_BOLD : 0));
    char buf[2] = {lp.letter, '\0'};
    mvprintw(offsetY + 1 + lp.pos.y, offsetX + 1 + lp.pos.x, "%s", buf);
    attroff(COLOR_PAIR(col) | (isCorrect ? A_BOLD : 0));
  }
}

void Renderer::drawHUD(int score, int level, const Board &board) const {
  attron(COLOR_PAIR(COL_HUD));
  mvprintw(0, 0, "Score: %d   Level: %d", score, level);
  mvprintw(offsetY + board.height + 5, offsetX,
           "Press Q quit | P pause | C change colors");
  attroff(COLOR_PAIR(COL_HUD));
  refresh();
}

void Renderer::drawPuzzleHUD(const WordPuzzle &puzzle, int solved, int total,
                             const Board &board) const {
  std::string display = puzzle.getDisplay();
  attron(COLOR_PAIR(COL_HUD) | A_BOLD);
  mvprintw(offsetY + board.height + 3, offsetX, "%s : %s", display.c_str(),
           puzzle.hint.c_str());
  mvprintw(offsetY + board.height + 4, offsetX, "Puzzles: %d / %d", solved,
           total);
  attroff(COLOR_PAIR(COL_HUD) | A_BOLD);
}

void Renderer::drawPaused(const Board &board) const {
  int centerY = offsetY + board.height / 2 - 3;
  int centerX = offsetX + (board.width - 48) / 2;

  attron(COLOR_PAIR(COL_PAUSE) | A_BOLD);
  mvprintw(centerY, centerX,
           "########     ###    ##     ##  ######  ######## ");
  mvprintw(centerY + 1, centerX,
           "##     ##   ## ##   ##     ## ##    ## ##       ");
  mvprintw(centerY + 2, centerX,
           "##     ##  ##   ##  ##     ## ##       ##       ");
  mvprintw(centerY + 3, centerX,
           "########  ##     ## ##     ##  ######  ######   ");
  mvprintw(centerY + 4, centerX,
           "##        ######### ##     ##       ## ##       ");
  mvprintw(centerY + 5, centerX,
           "##        ##     ## ##     ## ##    ## ##       ");
  mvprintw(centerY + 6, centerX,
           "##        ##     ##  #######   ######  ######## ");
  attroff(COLOR_PAIR(COL_PAUSE) | A_BOLD);

  attron(COLOR_PAIR(COL_HUD));
  mvprintw(centerY + 8, centerX + 10, "Press P to resume");
  attroff(COLOR_PAIR(COL_HUD));
  refresh();
}

char Renderer::drawGameOver(const Board &board, int score,
                            int puzzlesSolved) const {
  int cy = offsetY + board.height / 2 - 2;
  int cx = offsetX + board.width / 2 - 10;

  attron(COLOR_PAIR(COL_OBSTACLE) | A_BOLD);
  mvprintw(cy, cx, "========= GAME OVER =========");
  attroff(COLOR_PAIR(COL_OBSTACLE) | A_BOLD);

  attron(COLOR_PAIR(COL_HUD));
  mvprintw(cy + 2, cx, "  Score: %d", score);
  mvprintw(cy + 3, cx, "  Puzzles solved: %d", puzzlesSolved);
  mvprintw(cy + 5, cx, "  Press R to restart");
  mvprintw(cy + 6, cx, "  Press Q to quit");
  attroff(COLOR_PAIR(COL_HUD));

  refresh();

  // Wait for R or Q
  int key;
  while (true) {
    key = getch();
    if (key == 'r' || key == 'R')
      return 'r';
    if (key == 'q' || key == 'Q')
      return 'q';
  }
}

void Renderer::drawLevelComplete(const Board &board, int levelNum) const {
  int cy = offsetY + board.height / 2;
  int cx = offsetX + board.width / 2 - 8;
  attron(COLOR_PAIR(COL_LETTER_CORRECT) | A_BOLD);
  mvprintw(cy, cx, "LEVEL %d COMPLETE!", levelNum);
  mvprintw(cy + 1, cx, "Press any key to continue...");
  attroff(COLOR_PAIR(COL_LETTER_CORRECT) | A_BOLD);
  refresh();
  getch();
}

void Renderer::drawGameWon(const Board &board) const {
  int cy = offsetY + board.height / 2 - 1;
  int cx = offsetX + board.width / 2 - 10;
  attron(COLOR_PAIR(COL_LETTER_CORRECT) | A_BOLD);
  mvprintw(cy, cx, "=== CONGRATULATIONS! ===");
  mvprintw(cy + 1, cx, "  You solved all puzzles!");
  mvprintw(cy + 2, cx, "  Press any key to exit");
  attroff(COLOR_PAIR(COL_LETTER_CORRECT) | A_BOLD);
  refresh();
  getch();
}