#include "GameEngine.hpp"
#include "HighScoreManager.hpp"
#include "LevelLoader.hpp"
#include "Menu.hpp"
#include "Renderer.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

// ── Global state (needed for Emscripten main loop callback) ─────
static constexpr int LEVEL_COUNT = 3;

enum class AppState { MENU, PLAYING };

static AppState appState = AppState::MENU;
static MenuSystem menu;
static GameEngine *engine = nullptr;
static Level *levels[LEVEL_COUNT] = {};
static std::string levelFiles[LEVEL_COUNT] = {"data/level1.txt",
                                               "data/level2.txt",
                                               "data/level3.txt"};
static const std::string highScoreFile = "data/highscores.txt";
static int currentLevelIndex = 0;
static int carryPuzzles = 0;

// ── Start a level ────────────────────────────────────────────────
static void StartLevel(int levelIndex) {
  if (engine) {
    delete engine;
    engine = nullptr;
  }
  currentLevelIndex = levelIndex;
  engine = new GameEngine;
  *engine = GameEngine::create(*levels[levelIndex], menu.currentPalette);
  engine->puzzlesSolved = carryPuzzles;
  engine->puzzlesStartCount = carryPuzzles;
  appState = AppState::PLAYING;
}

// ── One frame ────────────────────────────────────────────────────
static void UpdateDrawFrame() {
  BeginDrawing();

  switch (appState) {
  case AppState::MENU: {
    menu.update(highScoreFile);
    menu.draw(levels, LEVEL_COUNT);

    // Check if a level was selected
    if (menu.selectedLevel >= 0) {
      carryPuzzles = 0;
      StartLevel(menu.selectedLevel);
      menu.selectedLevel = -1;
    }

    // Check quit
    if (menu.wantsQuit || WindowShouldClose()) {
#ifdef __EMSCRIPTEN__
      emscripten_cancel_main_loop();
#endif
    }
    break;
  }

  case AppState::PLAYING: {
    if (!engine) {
      appState = AppState::MENU;
      break;
    }

    engine->updateFrame();
    engine->drawFrame();

    if (!engine->running) {
      // Save score
      HighScoreManager::saveHighScore(
          highScoreFile, levels[currentLevelIndex]->levelNumber, engine->score,
          engine->puzzlesSolved);

      bool levelComplete = engine->checkLevelComplete();
      bool restart = engine->wantsRestart();
      carryPuzzles = engine->puzzlesSolved;

      if (levelComplete) {
        // Advance to next level
        int nextLevel = currentLevelIndex + 1;
        delete engine;
        engine = nullptr;

        if (nextLevel < LEVEL_COUNT) {
          StartLevel(nextLevel);
        } else {
          // All levels done — back to menu
          carryPuzzles = 0;
          appState = AppState::MENU;
        }
      } else if (restart) {
        // Replay same level
        StartLevel(currentLevelIndex);
      } else {
        // Quit to menu
        delete engine;
        engine = nullptr;
        carryPuzzles = 0;
        appState = AppState::MENU;
      }
    }

    if (WindowShouldClose()) {
      delete engine;
      engine = nullptr;
      appState = AppState::MENU;
    }
    break;
  }
  }

  EndDrawing();
}

// ── Entry point ──────────────────────────────────────────────────
int main() {
  srand(time(nullptr));

  // Load & validate all levels
  for (int i = 0; i < LEVEL_COUNT; i++) {
    levels[i] = LevelLoader::loadLevel(levelFiles[i]);
    if (levels[i] == nullptr) {
      return 1;
    }
    if (!LevelLoader::validateLevel(levels[i])) {
      return 1;
    }
  }

  // Load saved palette
  int palette = 0;
  {
    std::ifstream settingsIn("data/settings.txt");
    if (settingsIn.is_open()) {
      std::string line;
      while (std::getline(settingsIn, line)) {
        size_t eq = line.find('=');
        if (eq != std::string::npos) {
          std::string key = line.substr(0, eq);
          std::string val = line.substr(eq + 1);
          if (key == "palette")
            palette = std::stoi(val);
        }
      }
    }
  }

  // Init window
  InitWindow(Renderer::SCREEN_WIDTH, Renderer::SCREEN_HEIGHT,
             "Snake + Word Puzzle");
  SetTargetFPS(60);

  // Init menu
  menu.init(palette);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  while (!WindowShouldClose() && !menu.wantsQuit) {
    UpdateDrawFrame();
  }
#endif

  // Cleanup
  if (engine) {
    delete engine;
    engine = nullptr;
  }
  for (auto &level : levels) {
    LevelLoader::freeLevel(level);
  }
  CloseWindow();
  return 0;
}
