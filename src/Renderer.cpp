#include "Renderer.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>

// ── Palette definitions ──────────────────────────────────────────
static const Palette PALETTES[] = {
    // 0: Neon (default) — green snake on dark navy
    {
        {15, 15, 35, 255},     // background
        {20, 20, 45, 255},     // gameBg
        {30, 30, 55, 40},      // grid (subtle)
        {80, 80, 180, 255},    // border
        {220, 50, 60, 255},    // obstacle
        {50, 255, 120, 255},   // snakeHead
        {30, 200, 90, 255},    // snakeBody
        {255, 230, 50, 255},   // letterCorrect
        {100, 110, 180, 255},  // letterWrong
        {200, 210, 255, 255},  // hud
        {120, 100, 255, 255},  // accent
    },
    // 1: Ocean — cyan snake on deep teal
    {
        {10, 25, 35, 255},
        {15, 35, 50, 255},
        {25, 50, 65, 40},
        {40, 120, 160, 255},
        {40, 80, 180, 255},
        {0, 240, 255, 255},
        {0, 180, 200, 255},
        {100, 255, 150, 255},
        {180, 80, 80, 255},
        {180, 230, 255, 255},
        {0, 200, 220, 255},
    },
    // 2: Lava — orange snake on dark crimson
    {
        {30, 10, 10, 255},
        {45, 15, 15, 255},
        {60, 25, 25, 40},
        {200, 100, 30, 255},
        {255, 200, 40, 255},
        {255, 140, 30, 255},
        {220, 100, 20, 255},
        {255, 255, 255, 255},
        {180, 60, 200, 255},
        {255, 200, 150, 255},
        {255, 80, 30, 255},
    },
    // 3: Royal — magenta snake on deep purple
    {
        {20, 10, 30, 255},
        {30, 15, 45, 255},
        {45, 25, 60, 40},
        {120, 60, 200, 255},
        {200, 200, 220, 255},
        {255, 80, 220, 255},
        {200, 50, 180, 255},
        {255, 220, 50, 255},
        {220, 60, 60, 255},
        {230, 200, 255, 255},
        {180, 60, 255, 255},
    },
};
static constexpr int PALETTE_COUNT = 4;

// ── Init ─────────────────────────────────────────────────────────
void Renderer::init(int boardWidth, int boardHeight) {
  cellSize = 20;
  offsetX = (SCREEN_WIDTH - (boardWidth + 2) * cellSize) / 2;
  offsetY = 55; // room for top HUD
  currentPalette = 0;
  time = 0.0f;
  applyPalette(0);
}

void Renderer::update() { time += GetFrameTime(); }

void Renderer::applyPalette(int paletteIndex) {
  currentPalette = paletteIndex % PALETTE_COUNT;
  palette = PALETTES[currentPalette];
}

void Renderer::nextPalette() { applyPalette(currentPalette + 1); }

// ── Helpers ──────────────────────────────────────────────────────
static Color Glow(Color c, float alpha) {
  return {c.r, c.g, c.b, (unsigned char)(alpha * 255)};
}

static void DrawCenteredText(const char *text, int y, int fontSize, Color col) {
  int w = MeasureText(text, fontSize);
  DrawText(text, (Renderer::SCREEN_WIDTH - w) / 2, y, fontSize, col);
}

// ── Board ────────────────────────────────────────────────────────
void Renderer::drawBoard(const Board &board) const {
  // Game area background
  DrawRectangle(offsetX + cellSize, offsetY + cellSize, board.width * cellSize,
                board.height * cellSize, palette.gameBg);

  // Subtle grid lines
  for (int x = 0; x <= board.width; x++) {
    int px = offsetX + (x + 1) * cellSize;
    DrawLine(px, offsetY + cellSize,
             px, offsetY + (board.height + 1) * cellSize, palette.grid);
  }
  for (int y = 0; y <= board.height; y++) {
    int py = offsetY + (y + 1) * cellSize;
    DrawLine(offsetX + cellSize, py,
             offsetX + (board.width + 1) * cellSize, py, palette.grid);
  }

  // Border
  Rectangle borderRect = {(float)offsetX, (float)offsetY,
                           (float)((board.width + 2) * cellSize),
                           (float)((board.height + 2) * cellSize)};
  DrawRectangleLinesEx(borderRect, 2.0f, palette.border);

  // Obstacles
  for (const Obstacle &obs : board.obstacles) {
    for (const Position &cell : obs.cells) {
      Rectangle r = {(float)(offsetX + (cell.x + 1) * cellSize + 2),
                     (float)(offsetY + (cell.y + 1) * cellSize + 2),
                     (float)(cellSize - 4), (float)(cellSize - 4)};
      DrawRectangleRounded(r, 0.3f, 4, palette.obstacle);
    }
  }
}

// ── Snake ────────────────────────────────────────────────────────
void Renderer::drawSnake(const Snake &snake) const {
  // Body segments (back to front, skip head)
  for (int i = snake.body.size() - 1; i >= 1; --i) {
    Position p = snake.body.at(i);
    Rectangle r = {(float)(offsetX + (p.x + 1) * cellSize + 2),
                   (float)(offsetY + (p.y + 1) * cellSize + 2),
                   (float)(cellSize - 4), (float)(cellSize - 4)};
    float fade = 0.5f + 0.5f * (1.0f - (float)i / snake.body.size());
    Color bodyCol = {palette.snakeBody.r, palette.snakeBody.g,
                     palette.snakeBody.b, (unsigned char)(fade * 255)};
    DrawRectangleRounded(r, 0.4f, 4, bodyCol);
  }

  // Head (larger, brighter)
  Position head = snake.getHead();
  Rectangle hr = {(float)(offsetX + (head.x + 1) * cellSize + 1),
                  (float)(offsetY + (head.y + 1) * cellSize + 1),
                  (float)(cellSize - 2), (float)(cellSize - 2)};

  // Glow behind head
  Rectangle glowR = {hr.x - 2, hr.y - 2, hr.width + 4, hr.height + 4};
  DrawRectangleRounded(glowR, 0.5f, 4, Glow(palette.snakeHead, 0.25f));
  DrawRectangleRounded(hr, 0.5f, 4, palette.snakeHead);

  // Eyes based on direction
  int eyeSize = 3;
  int ex1, ey1, ex2, ey2;
  int cx = offsetX + (head.x + 1) * cellSize;
  int cy = offsetY + (head.y + 1) * cellSize;

  switch (snake.currentDirection) {
  case Direction::RIGHT:
    ex1 = cx + cellSize - 5; ey1 = cy + 4;
    ex2 = cx + cellSize - 5; ey2 = cy + cellSize - 7;
    break;
  case Direction::LEFT:
    ex1 = cx + 3; ey1 = cy + 4;
    ex2 = cx + 3; ey2 = cy + cellSize - 7;
    break;
  case Direction::UP:
    ex1 = cx + 4;            ey1 = cy + 3;
    ex2 = cx + cellSize - 7; ey2 = cy + 3;
    break;
  case Direction::DOWN:
    ex1 = cx + 4;            ey1 = cy + cellSize - 5;
    ex2 = cx + cellSize - 7; ey2 = cy + cellSize - 5;
    break;
  }
  DrawRectangle(ex1, ey1, eyeSize, eyeSize, palette.background);
  DrawRectangle(ex2, ey2, eyeSize, eyeSize, palette.background);
}

// ── Letters ──────────────────────────────────────────────────────
void Renderer::drawLetters(const std::vector<LetterPickup> &letters,
                           const WordPuzzle &puzzle) const {
  auto missing = puzzle.getMissingLetters();

  for (const LetterPickup &lp : letters) {
    bool isCorrect = missing.count(lp.letter) > 0;
    Color col = isCorrect ? palette.letterCorrect : palette.letterWrong;

    int px = offsetX + (lp.pos.x + 1) * cellSize;
    int py = offsetY + (lp.pos.y + 1) * cellSize;

    // Pulsing glow for correct letters
    if (isCorrect) {
      float pulse = 0.15f + 0.1f * sinf(time * 4.0f);
      Rectangle glowR = {(float)(px - 2), (float)(py - 2),
                          (float)(cellSize + 4), (float)(cellSize + 4)};
      DrawRectangleRounded(glowR, 0.3f, 4, Glow(col, pulse));
    }

    // Background circle/rect
    Rectangle r = {(float)(px + 1), (float)(py + 1), (float)(cellSize - 2),
                   (float)(cellSize - 2)};
    DrawRectangleRounded(r, 0.4f, 4, Glow(col, 0.3f));

    // Letter text
    char buf[2] = {lp.letter, '\0'};
    int tw = MeasureText(buf, 16);
    DrawText(buf, px + (cellSize - tw) / 2, py + 2, 16, col);
  }
}

// ── HUD ──────────────────────────────────────────────────────────
void Renderer::drawHUD(int score, int level, const Board &board) const {
  char buf[64];
  snprintf(buf, sizeof(buf), "SCORE: %d", score);
  DrawText(buf, offsetX + 5, 15, 22, palette.hud);

  snprintf(buf, sizeof(buf), "LEVEL: %d", level);
  int w = MeasureText(buf, 22);
  DrawText(buf, offsetX + (board.width + 2) * cellSize - w - 5, 15, 22,
           palette.hud);

  // Controls hint at bottom
  int bottomY = offsetY + (board.height + 2) * cellSize + 45;
  DrawText("WASD / Arrows: Move   P: Pause   Q: Quit", offsetX + 5, bottomY,
           14, Glow(palette.hud, 0.4f));
}

void Renderer::drawPuzzleHUD(const WordPuzzle &puzzle, int solved, int total,
                              const Board &board) const {
  int bottomY = offsetY + (board.height + 2) * cellSize + 8;

  // Puzzle word display
  std::string display = puzzle.getDisplay();
  char buf[256];
  snprintf(buf, sizeof(buf), "%s  :  %s", display.c_str(), puzzle.hint.c_str());
  DrawText(buf, offsetX + 5, bottomY, 18, palette.accent);

  // Puzzles solved counter
  snprintf(buf, sizeof(buf), "Puzzles: %d / %d", solved, total);
  int w = MeasureText(buf, 18);
  DrawText(buf, offsetX + (board.width + 2) * cellSize - w - 5, bottomY, 18,
           palette.hud);
}

// ── Overlays ─────────────────────────────────────────────────────
void Renderer::drawOverlay(const char *title, const char *line1,
                           const char *line2, const Board &board) const {
  // Darken background
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, {0, 0, 0, 160});

  int cy = SCREEN_HEIGHT / 2 - 60;

  // Title
  DrawCenteredText(title, cy, 36, palette.accent);

  // Lines
  if (line1 && strlen(line1) > 0)
    DrawCenteredText(line1, cy + 50, 20, palette.hud);
  if (line2 && strlen(line2) > 0)
    DrawCenteredText(line2, cy + 80, 20, palette.hud);
}

void Renderer::drawPaused(const Board &board) const {
  drawOverlay("PAUSED", "Press P to resume", "", board);
}

void Renderer::drawGameOver(const Board &board, int score,
                             int puzzlesSolved) const {
  char line1[64], line2[64];
  snprintf(line1, sizeof(line1), "Score: %d  |  Puzzles Solved: %d", score,
           puzzlesSolved);
  snprintf(line2, sizeof(line2), "Press R to Restart  |  Press Q to Quit");
  drawOverlay("GAME OVER", line1, line2, board);
}

void Renderer::drawLevelComplete(const Board &board, int levelNum) const {
  char buf[64];
  snprintf(buf, sizeof(buf), "LEVEL %d COMPLETE!", levelNum);
  drawOverlay(buf, "Press any key to continue...", "", board);
}

void Renderer::drawGameWon(const Board &board) const {
  drawOverlay("CONGRATULATIONS!", "You solved all puzzles!",
              "Press any key to return to menu", board);
}