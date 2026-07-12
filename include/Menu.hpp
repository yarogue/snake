#pragma once
#include "Level.hpp"
#include "Renderer.hpp"
#include <string>

enum class MenuScreen {
  MAIN,
  HIGH_SCORES,
  SETTINGS,
};

struct MenuSystem {
  MenuScreen screen;
  int selectedOption;
  int currentPalette;
  int selectedLevel; // -1 = none, 0-2 = level to start
  bool wantsQuit;
  Renderer renderer;
  float time;

  // High score display cache
  std::string highScoreText;

  void init(int palette);
  void update(const std::string &highScoreFile);
  void draw(Level *levels[], int levelCount);
  void drawMainMenu();
  void drawHighScores();
  void drawSettings();
};
