# 🐍 Snake Word Puzzle

A terminal-based Snake game with an educational twist — collect letters to solve word puzzles while navigating obstacles. Built in C++ with ncurses.

## 🎮 How It Works

The classic Snake game meets word puzzles. Each level presents a series of clues — guide the snake to collect the correct letters and spell out the answer while avoiding obstacles, walls, and your own tail.

- **3 difficulty levels** with unique word sets (medieval/knight theme)
- **Dynamic letter spawning** — correct and decoy letters appear on the board
- **Color palette switching** — press `C` during gameplay to cycle themes
- **Persistent high scores** — saved between sessions
- **Level progression** with increasing speed and obstacles

## 🏗️ Architecture

```
main.cpp                    ← Entry point: loads levels, runs menu
│
├── LevelLoader (.hpp/.cpp) ← Reads level data from external .txt files
├── HighScoreManager        ← Loads/saves scores to disk
├── Menu (.hpp/.cpp)        ← Terminal menu: play, highscores, settings, quit
│
└── GameEngine (.hpp/.cpp)  ← Core game loop
    ├── Snake (.hpp/.cpp)   ← Snake body & movement (custom linked list)
    ├── Board (.hpp/.cpp)   ← Grid, obstacles, wrapping
    ├── Renderer (.hpp/.cpp)← ncurses drawing
    ├── InputHandler        ← Keyboard input
    └── WordPuzzle          ← Puzzle state & letter tracking
```

## 📂 Project Structure

```
snake/
├── data/                   ← External game data (NOT hardcoded)
│   ├── level1.txt          Easy: 10 puzzles, 200ms tick
│   ├── level2.txt          Medium: 15 puzzles, 150ms tick
│   ├── level3.txt          Hard: 20 puzzles, 100ms tick
│   └── highscores.txt      Persistent scores per level
│
├── include/                ← Header files
│   ├── LevelLoader.hpp     Load/validate/free levels from files
│   ├── HighScoreManager.hpp Persistent high score management
│   ├── Menu.hpp            Main menu system
│   ├── GameEngine.hpp      Core game loop & state
│   ├── Snake.hpp           Snake body (linked list)
│   ├── Board.hpp           Grid & obstacles
│   ├── Renderer.hpp        ncurses rendering
│   ├── LinkedList.hpp      Custom linked list (raw pointers)
│   ├── WordPuzzle.hpp      Puzzle logic
│   ├── Level.hpp           Level data struct
│   └── ...                 Supporting types
│
├── src/                    ← Implementation files
│   ├── LevelLoader.cpp     File parsing with ifstream
│   ├── HighScoreManager.cpp Score persistence
│   ├── Menu.cpp            Text-based command menu
│   ├── GameEngine.cpp      Game loop, collision, puzzles
│   ├── Snake.cpp           Movement & growth
│   ├── Board.cpp           Obstacle generation
│   ├── Renderer.cpp        Terminal drawing
│   └── LinkedList.cpp      Node allocation with new/delete
│
├── main.cpp                Entry point
├── CMakeLists.txt          Build configuration
└── docs/
    └── assessment.md       This file
```

## 🔧 Build & Run

**Prerequisites:** C++20 compiler, CMake 3.16+, ncurses

```bash
# Build
cd snake
mkdir -p cmake-build-debug && cd cmake-build-debug
cmake ..
make

# Run (from project root — data files use relative paths)
cd ..
./cmake-build-debug/snake
```

## 📊 Data-Driven Design

Level data is stored in **external text files**, not hardcoded. This means levels can be modified without recompiling:

```
levelNumber=1
boardWidth=50
boardHeight=20
obstacleCount=3
initialSnakeLen=3
tickIntervalMs=200
puzzlesToSolve=3

[puzzles]
WIZARD|Man with magical powers
KING|The man who reigns on England
SWORD|Weapon the knight uses to defend himself
```

`LevelLoader::loadLevel()` parses these files using `std::ifstream`, allocates the `Level` struct with `new`, and returns a pointer. The caller frees it with `LevelLoader::freeLevel()` (`delete`).

## 🧠 Key Technical Concepts

| Concept | Implementation |
|---------|---------------|
| **Dynamic memory** | `new`/`delete` for levels, `new[]`/`delete[]` for high scores, `new Node`/`delete` for linked list |
| **File I/O** | `std::ifstream` for reading levels & scores, `std::ofstream` for saving |
| **Data-driven design** | All game content loaded from `data/` files at runtime |
| **Custom data structure** | Hand-built singly-linked list replaces `std::deque` for snake body |
| **Separation of concerns** | Each module has a single responsibility (loading, rendering, input, etc.) |
| **Input validation** | `validateLevel()` checks all loaded data before use |

## 🎯 Controls

| Key | Action |
|-----|--------|
| `↑ ↓ ← →` / `W A S D` | Move snake |
| `P` | Pause / unpause |
| `C` | Cycle color palette |
| `Q` | Quit |
| `R` | Restart level (on game over) |
