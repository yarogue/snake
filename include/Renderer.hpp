#pragma once
#include "Board.hpp"
#include "LetterPickup.hpp"
#include "Position.hpp"
#include "Snake.hpp"
#include "WordPuzzle.hpp"
#include <vector>
#include "raylib.h"

struct Palette {
  Color background;
  Color gameBg;
  Color grid;
  Color border;
  Color obstacle;
  Color snakeHead;
  Color snakeBody;
  Color letterCorrect;
  Color letterWrong;
  Color hud;
  Color accent;
};

struct Renderer {
  int offsetX;
  int offsetY;
  int cellSize;
  int currentPalette;
  Palette palette;
  float time; // for animations

  void init(int boardWidth, int boardHeight);
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
  void drawGameOver(const Board &board, int score, int puzzlesSolved) const;
  void drawLevelComplete(const Board &board, int levelNum) const;
  void drawGameWon(const Board &board) const;
  void drawOverlay(const char *title, const char *line1, const char *line2,
                   const Board &board) const;
  void update(); // call each frame for animation timers

  static constexpr int SCREEN_WIDTH = 1060;
  static constexpr int SCREEN_HEIGHT = 640;
};
