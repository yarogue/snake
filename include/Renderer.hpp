#pragma once
#include "Board.hpp"
#include "LetterPickup.hpp"
#include "Position.hpp"
#include "Snake.hpp"
#include "WordPuzzle.hpp"
#include <vector>

// Color pair IDs
enum ColorID {
  COL_BORDER = 1,
  COL_OBSTACLE,
  COL_SNAKE_HEAD,
  COL_SNAKE_BODY,
  COL_LETTER_CORRECT,
  COL_LETTER_WRONG,
  COL_HUD,
  COL_PAUSE
};

struct Renderer {
  int offsetX;
  int offsetY;
  int currentPalette;

  void init();
  void shutdown();
  void applyPalette(int paletteIndex);
  void nextPalette();
  void drawBoard(const Board &board) const;
  void drawSnake(const Snake &snake) const;
  void drawLetters(const std::vector<LetterPickup> &letters,
                   const WordPuzzle &puzzle) const;
  void drawHUD(int score, int level, const Board &board) const;
  void drawPuzzleHUD(const WordPuzzle &puzzle, int solved, int total,
                     const Board &board) const;
  void drawPaused(const Board &board) const;
  char drawGameOver(const Board &board, int score, int puzzlesSolved) const;
  void drawLevelComplete(const Board &board, int levelNum) const;
  void drawGameWon(const Board &board) const;
};
