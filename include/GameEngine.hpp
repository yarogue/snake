#pragma once
#include "Board.hpp"
#include "Snake.hpp"
#include "Level.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "Position.hpp"

struct GameEngine {

  // Members:
    Board        board;
    Snake        snake;
    Level        currentLevel;
    Renderer     renderer;
    InputHandler inputHandler;
    Position     foodPos;
    int          score;
    bool         running;

  //Methods:
    void run();
    void update();
    void spawnFood();
    void handleFoodEaten();
    void handleDeath();
    bool checkWallOrObstacleCollision() const;
    bool checkSelfCollision() const;
    static GameEngine create(const Level& level);
};
