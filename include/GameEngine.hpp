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

enum class GameState {
  PLAYING,
  PAUSED,
  GAME_OVER,
  LEVEL_COMPLETE,
  GAME_WON
};

struct GameEngine {

  // Members:
  Board board;
  Snake snake;
  Level currentLevel;
  Renderer renderer;
  InputHandler inputHandler;
  int score;
  bool running;
  GameState state;
  char lastDeathChoice; // 'r' restart, 'q' quit

  // Timing
  float tickTimer;
  float tickInterval; // seconds per game tick

  // Puzzle state
  WordPuzzle currentPuzzle;
  std::vector<LetterPickup> letters;
  int puzzlesSolved;
  int puzzleIndex;
  int puzzlesStartCount; // baseline when level starts

  // Methods:
  void updateFrame();
  void drawFrame();
  void gameTick(); // one logic step
  void spawnLetters();
  void handleLetterPickup();
  void nextPuzzle();
  bool checkLevelComplete() const;
  bool checkWallOrObstacleCollision() const;
  bool checkSelfCollision() const;
  bool wantsRestart() const;
  static GameEngine create(const Level &level, int palette = 0);
};
