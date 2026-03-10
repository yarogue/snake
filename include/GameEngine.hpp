#pragma once
#include "Board.hpp"
#include "InputHandler.hpp"
#include "LetterPickup.hpp"
#include "Level.hpp"
#include "Position.hpp"
#include "Renderer.hpp"
#include "Snake.hpp"
#include "WordPuzzle.hpp"
#include <vector>

struct GameEngine {

  // Members:
  Board board;
  Snake snake;
  Level currentLevel;
  Renderer renderer;
  InputHandler inputHandler;
  int score;
  bool running;
  bool paused;
  char lastDeathChoice; // 'r' restart, 'q' quit

  // Puzzle state
  WordPuzzle currentPuzzle;
  std::vector<LetterPickup> letters;
  int puzzlesSolved;
  int puzzleIndex;
  int puzzlesStartCount; // baseline when level starts

  // Methods:
  void run();
  void update();
  void spawnLetters();
  void handleLetterPickup();
  void nextPuzzle();
  bool checkLevelComplete() const;
  void handleDeath();
  bool checkWallOrObstacleCollision() const;
  bool checkSelfCollision() const;
  bool wantsRestart() const;
  static GameEngine create(const Level &level);
};
