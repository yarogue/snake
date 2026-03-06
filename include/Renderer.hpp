#pragma once
#include "Board.hpp"
#include "Position.hpp"
#include "Snake.hpp"

struct Renderer {
  int offsetX;
  int offsetY;

  void init();
  void shutdown();
  void drawBoard(const Board &board) const;
  void drawSnake(const Snake &snake) const;
  void drawFood(Position foodPos) const;
  void drawHUD(int score, int level, const Board &board) const;
  void drawPaused(const Board &board) const;
  void drawGameOver(const Board &board) const;
};
