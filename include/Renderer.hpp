#pragma once
#include "Board.hpp"
#include "Snake.hpp"
#include "Position.hpp"

struct Renderer {
    int offsetX;
    int offsetY;

    void init();
    void shutdown();
    void drawBoard(const Board& board) const;
    void drawSnake(const Snake& snake) const;
    void drawFood(Position foodPos) const;
    void drawHUD(int score, int level) const;
    void drawGameOver(const Board& board) const;
};
