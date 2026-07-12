#include "Menu.hpp"
#include "HighScoreManager.hpp"
#include "raylib.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <cstring>

static const char *MENU_OPTIONS[] = {"Play Level 1", "Play Level 2",
                                     "Play Level 3", "High Scores",
                                     "Settings",     "Quit"};
static constexpr int MENU_OPTION_COUNT = 6;

static void DrawCentered(const char *text, int y, int fontSize, Color col) {
  int w = MeasureText(text, fontSize);
  DrawText(text, (Renderer::SCREEN_WIDTH - w) / 2, y, fontSize, col);
}

void MenuSystem::init(int palette) {
  screen = MenuScreen::MAIN;
  selectedOption = 0;
  currentPalette = palette;
  selectedLevel = -1;
  wantsQuit = false;
  time = 0.0f;
  renderer.init(50, 20);
  renderer.applyPalette(palette);
}

void MenuSystem::update(const std::string &highScoreFile) {
  time += GetFrameTime();

  switch (screen) {
  case MenuScreen::MAIN:
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
      selectedOption =
          (selectedOption - 1 + MENU_OPTION_COUNT) % MENU_OPTION_COUNT;
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
      selectedOption = (selectedOption + 1) % MENU_OPTION_COUNT;
    }
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
      switch (selectedOption) {
      case 0:
      case 1:
      case 2:
        selectedLevel = selectedOption;
        break;
      case 3: {
        // Load high scores for display
        int count = 0;
        auto *entries =
            HighScoreManager::loadHighScores(highScoreFile, count);
        highScoreText = "";
        if (entries && count > 0) {
          for (int i = 0; i < count; i++) {
            char buf[128];
            snprintf(buf, sizeof(buf), "Level %d   Score: %d   Puzzles: %d",
                     entries[i].level, entries[i].score,
                     entries[i].puzzlesSolved);
            highScoreText += buf;
            highScoreText += "\n";
          }
          HighScoreManager::freeHighScores(entries);
        } else {
          highScoreText = "No high scores yet.";
        }
        screen = MenuScreen::HIGH_SCORES;
        break;
      }
      case 4:
        screen = MenuScreen::SETTINGS;
        break;
      case 5:
        wantsQuit = true;
        break;
      }
    }
    // Quick level select with number keys
    if (IsKeyPressed(KEY_ONE))   selectedLevel = 0;
    if (IsKeyPressed(KEY_TWO))   selectedLevel = 1;
    if (IsKeyPressed(KEY_THREE)) selectedLevel = 2;
    if (IsKeyPressed(KEY_Q))     wantsQuit = true;
    break;

  case MenuScreen::HIGH_SCORES:
    if (GetKeyPressed() != 0) {
      screen = MenuScreen::MAIN;
    }
    break;

  case MenuScreen::SETTINGS:
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
      currentPalette = (currentPalette - 1 + 4) % 4;
      renderer.applyPalette(currentPalette);
      // Save to file
      std::ofstream out("data/settings.txt");
      if (out.is_open()) {
        out << "palette=" << currentPalette << "\n";
      }
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
      currentPalette = (currentPalette + 1) % 4;
      renderer.applyPalette(currentPalette);
      std::ofstream out("data/settings.txt");
      if (out.is_open()) {
        out << "palette=" << currentPalette << "\n";
      }
    }
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) ||
        IsKeyPressed(KEY_BACKSPACE)) {
      screen = MenuScreen::MAIN;
    }
    break;
  }
}

void MenuSystem::draw(Level *levels[], int levelCount) {
  ClearBackground(renderer.palette.background);

  switch (screen) {
  case MenuScreen::MAIN:
    drawMainMenu();
    break;
  case MenuScreen::HIGH_SCORES:
    drawHighScores();
    break;
  case MenuScreen::SETTINGS:
    drawSettings();
    break;
  }
}

void MenuSystem::drawMainMenu() {
  // Title
  float titlePulse = 1.0f + 0.05f * sinf(time * 2.0f);
  int titleSize = (int)(42 * titlePulse);
  DrawCentered("SNAKE + WORD PUZZLE", 100, titleSize, renderer.palette.accent);

  // Subtitle
  DrawCentered("Collect letters. Solve words. Survive.",
               155, 18, renderer.palette.hud);

  // Decorative line
  int lineY = 190;
  int lineW = 400;
  int lineX = (Renderer::SCREEN_WIDTH - lineW) / 2;
  DrawRectangle(lineX, lineY, lineW, 2, renderer.palette.border);

  // Menu options
  int startY = 220;
  int spacing = 45;

  for (int i = 0; i < MENU_OPTION_COUNT; i++) {
    int y = startY + i * spacing;
    bool selected = (i == selectedOption);

    if (selected) {
      // Highlight bar
      int textW = MeasureText(MENU_OPTIONS[i], 24);
      int barW = textW + 40;
      int barX = (Renderer::SCREEN_WIDTH - barW) / 2;
      DrawRectangleRounded({(float)barX, (float)(y - 5), (float)barW, 35.0f},
                           0.3f, 4,
                           {renderer.palette.accent.r,
                            renderer.palette.accent.g,
                            renderer.palette.accent.b, 40});

      // Arrow indicator
      float bounce = 3.0f * sinf(time * 5.0f);
      DrawText(">", barX + 5 + (int)bounce, y, 24, renderer.palette.accent);

      DrawCentered(MENU_OPTIONS[i], y, 24, renderer.palette.accent);
    } else {
      DrawCentered(MENU_OPTIONS[i], y, 22, renderer.palette.hud);
    }
  }

  // Controls hint
  DrawCentered("Arrow Keys / WASD to navigate   Enter to select",
               560, 14, {renderer.palette.hud.r, renderer.palette.hud.g,
                         renderer.palette.hud.b, 100});
}

void MenuSystem::drawHighScores() {
  DrawCentered("HIGH SCORES", 80, 36, renderer.palette.accent);

  // Parse and display scores
  int y = 160;
  std::istringstream stream(highScoreText);
  std::string line;
  while (std::getline(stream, line)) {
    DrawCentered(line.c_str(), y, 22, renderer.palette.hud);
    y += 35;
  }

  DrawCentered("Press any key to return", 520, 16, renderer.palette.border);
}

void MenuSystem::drawSettings() {
  DrawCentered("SETTINGS", 80, 36, renderer.palette.accent);

  // Palette selector
  DrawCentered("Color Palette", 180, 22, renderer.palette.hud);

  static const char *PALETTE_NAMES[] = {"Neon", "Ocean", "Lava", "Royal"};
  char buf[64];
  snprintf(buf, sizeof(buf), "< %s >", PALETTE_NAMES[currentPalette]);
  DrawCentered(buf, 230, 28, renderer.palette.accent);

  // Color preview
  int previewY = 290;
  int previewX = Renderer::SCREEN_WIDTH / 2 - 120;
  int swatchSize = 30;
  int gap = 10;

  struct { const char* label; Color col; } swatches[] = {
    {"Snake", renderer.palette.snakeHead},
    {"Body",  renderer.palette.snakeBody},
    {"Border", renderer.palette.border},
    {"Obstacle", renderer.palette.obstacle},
    {"Letter", renderer.palette.letterCorrect},
    {"Accent", renderer.palette.accent},
  };

  for (int i = 0; i < 6; i++) {
    int x = previewX + i * (swatchSize + gap);
    DrawRectangleRounded(
        {(float)x, (float)previewY, (float)swatchSize, (float)swatchSize},
        0.3f, 4, swatches[i].col);
    int tw = MeasureText(swatches[i].label, 10);
    DrawText(swatches[i].label, x + (swatchSize - tw) / 2,
             previewY + swatchSize + 5, 10, renderer.palette.hud);
  }

  DrawCentered("Left/Right to change   Enter to confirm",
               420, 16, renderer.palette.border);
}
