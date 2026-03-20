# Architecture Diagram

## Module Overview

```
╔══════════════════════════════════════════════════════════════════╗
║                          main.cpp                                ║
║  - Seeds random                                                  ║
║  - Loads & validates levels via LevelLoader                      ║
║  - Launches Menu::menuLoop()                                     ║
║  - Frees all levels on exit                                      ║
╚══════════════╦═══════════════╦═══════════════╦═══════════════════╝
               │               │               │
               ▼               ▼               ▼
     ┌─────────────┐  ┌──────────────┐  ┌──────────────────┐
     │ LevelLoader │  │    Menu      │  │ HighScoreManager │
     │─────────────│  │──────────────│  │──────────────────│
     │ loadLevel() │  │ showMenu()   │  │ loadHighScores() │
     │ validate()  │  │ menuLoop()   │  │ saveHighScore()  │
     │ freeLevel() │  │ handlePlay() │  │ printHighScores()│
     │             │  │handleSettings│  │ freeHighScores() │
     └─────────────┘  └───────┬──────┘  └──────────────────┘
                              │                    ▲
      data/level1-3.txt ──────┤                    │
                              ▼                    │
                    ┌──────────────────┐           │
                    │   GameEngine     │───────────┘
                    │──────────────────│    saves scores
                    │ create()         │    after each level
                    │ run()            │
                    │ update()         │
                    │ handleDeath()    │
                    │ nextPuzzle()     │
                    └────┬─────┬───┬──┘
                         │     │   │
              ┌──────────┘     │   └──────────┐
              ▼                ▼              ▼
     ┌──────────────┐  ┌────────────┐  ┌──────────────┐
     │    Snake      │  │  Board     │  │  Renderer    │
     │──────────────│  │────────────│  │──────────────│
     │ move()       │  │ wrap()     │  │ init()       │
     │ grow()       │  │ isObstacle │  │ shutdown()   │
     │ getHead()    │  │ generate() │  │ drawBoard()  │
     │ setDirection │  │            │  │ drawSnake()  │
     │              │  │            │  │ drawHUD()    │
     │ body:        │  │            │  │ drawLetters()│
     │ LinkedList ──┤  └────────────┘  └──────────────┘
     └──────────────┘         
              │                
              ▼                
     ┌──────────────┐  ┌──────────────┐  ┌──────────────┐
     │  LinkedList  │  │ InputHandler │  │  WordPuzzle  │
     │──────────────│  │──────────────│  │──────────────│
     │ pushFront()  │  │ pollInput()  │  │ create()     │
     │ popFront()   │  │ isQuitKey()  │  │ tryLetter()  │
     │ popBack()    │  │              │  │ isComplete() │
     │ front()      │  │              │  │ getMissing() │
     │ size()       │  │              │  │              │
     │ at(index)    │  │              │  │              │
     │ contains()   │  │              │  │              │
     │              │  │              │  │              │
     │ Node* head   │  │              │  │              │
     │ new/delete   │  │              │  │              │
     └──────────────┘  └──────────────┘  └──────────────┘
```

## Data Flow

```
                    STARTUP
                       │
         ┌─────────────┼──────────────┐
         ▼             ▼              ▼
    level1.txt    level2.txt     level3.txt
         │             │              │
         └──────┬──────┘──────────────┘
                │  LevelLoader::loadLevel()
                ▼  (new Level)
         Level* levels[3]
                │
                ▼
        Menu::menuLoop()
           │         │
     "h"   │    "1"  │
     ──────▼──  ─────▼──────────────────────────
     printHighScores()   handlePlay()
           │                   │
           ▼                   ▼
     highscores.txt      GameEngine (new/delete)
                               │
                          ┌────┴────┐
                          │  run()  │  ← game loop
                          │ update  │
                          │ render  │
                          └────┬────┘
                               │
                          saveHighScore()
                               │
                               ▼
                         highscores.txt
                    
                    SHUTDOWN
                       │
                LevelLoader::freeLevel()
                  (delete level)
```

## Memory Management

| Allocation          | Where             | Deallocation        | Where              |
|---------------------|-------------------|---------------------|--------------------|
| `new Level`         | `loadLevel()`     | `delete level`      | `freeLevel()`      |
| `new HighScoreEntry[]` | `loadHighScores()` | `delete[] entries` | `freeHighScores()` |
| `new GameEngine`    | `handlePlay()`    | `delete engine`     | `handlePlay()`     |
| `new Node`          | `pushFront()`     | `delete node`       | `popBack/Front/~`  |

## File Structure

```
snake/
├── main.cpp                ← Entry point (load → menu → free)
├── include/
│   ├── Level.hpp           ← Level data struct
│   ├── LevelLoader.hpp     ← Load/validate/free levels
│   ├── HighScoreManager.hpp← Score persistence
│   ├── Menu.hpp            ← Menu system
│   ├── GameEngine.hpp      ← Core game loop
│   ├── Snake.hpp           ← Snake struct (uses LinkedList)
│   ├── LinkedList.hpp      ← Custom linked list (replaces deque)
│   ├── Board.hpp           ← Grid & obstacles
│   ├── Renderer.hpp        ← ncurses drawing
│   ├── InputHandler.hpp    ← Keyboard input
│   ├── WordPuzzle.hpp      ← Puzzle logic
│   ├── Position.hpp        ← x,y coordinate
│   ├── Direction.hpp       ← UP/DOWN/LEFT/RIGHT
│   ├── LetterPickup.hpp    ← Letter on the board
│   └── Obstacle.hpp        ← Obstacle position
├── src/                    ← Matching .cpp files
├── data/
│   ├── level1-3.txt        ← Level configs + puzzles
│   └── highscores.txt      ← Persistent scores (CSV)
└── docs/
    ├── assessment.md       ← Project README
    └── architecture.md     ← This file
```
