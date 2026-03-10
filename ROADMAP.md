# Assessment 3 — Implementation Roadmap

Work through these in order. Each TODO has pseudocode in the source file.

## Phase 1: Load Levels from Files
> Files: `src/LevelLoader.cpp` + `include/LevelLoader.hpp`
> Data:  `data/level1.txt`, `data/level2.txt`, `data/level3.txt`

| Step | File | What to do |
|------|------|------------|
| **1a** | `src/LevelLoader.cpp` | Implement `loadLevel()` — read file, parse key=value + puzzles, return `new Level` |
| **1b** | `src/LevelLoader.cpp` | Implement `validateLevel()` — check all fields are valid |
| **1c** | `src/LevelLoader.cpp` | Implement `freeLevel()` — call `delete level` |

**Test:** Write a quick test in `main.cpp` that loads level1.txt, prints values, then frees it.

---

## Phase 2: Persistent High Scores
> Files: `src/HighScoreManager.cpp` + `include/HighScoreManager.hpp`
> Data:  `data/highscores.txt`

| Step | File | What to do |
|------|------|------------|
| **2a** | `src/HighScoreManager.cpp` | Implement `loadHighScores()` — parse CSV, return `new HighScoreEntry[]` |
| **2b** | `src/HighScoreManager.cpp` | Implement `saveHighScore()` — load, update if better, write back |
| **2c** | `src/HighScoreManager.cpp` | Implement `printHighScores()` — load + print formatted table |
| **2d** | `src/HighScoreManager.cpp` | Implement `freeHighScores()` — call `delete[] entries` |

**Test:** In `main.cpp`, save a score, then print highscores to verify file read/write works.

---

## Phase 3: Main Menu
> Files: `src/Menu.cpp` + `include/Menu.hpp`

| Step | File | What to do |
|------|------|------------|
| **3a** | `src/Menu.cpp` | Implement `showMenu()` — print the banner + commands |
| **3b** | `src/Menu.cpp` | Implement `menuLoop()` — read commands, dispatch to handlers |
| **3c** | `src/Menu.cpp` | Implement `handlePlay()` — level progression loop (moved from old `main.cpp`) with `new`/`delete` for GameEngine |
| **3d** | `src/Menu.cpp` | Implement `handleSettings()` — simple color palette picker |

**Test:** Run the game. You should see the menu, be able to type `play 1`, `highscores`, `quit`.

---

## Phase 4: Wire Up main.cpp
> File: `main.cpp`

| Step | File | What to do |
|------|------|------------|
| **4a** | `main.cpp` | Load 3 levels with `LevelLoader::loadLevel()` |
| **4b** | `main.cpp` | Validate each with `LevelLoader::validateLevel()` |
| **4c** | `main.cpp` | Call `Menu::menuLoop()` |
| **4d** | `main.cpp` | Free all levels with `LevelLoader::freeLevel()` at the end |

**Test:** Full integration — start game, menu works, play level, save score, quit, restart, scores persist.

---

## Phase 5: Save Scores During Gameplay
> File: `src/Menu.cpp` (inside `handlePlay`)

| Step | File | What to do |
|------|------|------------|
| **5a** | `src/Menu.cpp` | After level complete → call `HighScoreManager::saveHighScore()` |
| **5b** | `src/Menu.cpp` | After game over → save score if it's a new high |

---

## Phase 6 (Extra): Custom Linked List
> Files: `src/LinkedList.cpp` + `include/LinkedList.hpp`

| Step | File | What to do |
|------|------|------------|
| **6a** | `src/LinkedList.cpp` | Constructor — init head/length |
| **6b** | `src/LinkedList.cpp` | Destructor — walk + delete all nodes |
| **6c** | `src/LinkedList.cpp` | `pushFront()` — `new Node`, link to head |
| **6d** | `src/LinkedList.cpp` | `popBack()` — walk to second-to-last, `delete` last |
| **6e** | `src/LinkedList.cpp` | `front()` — return head data |
| **6f** | `src/LinkedList.cpp` | `size()` — return length |
| **6g** | `src/LinkedList.cpp` | `at(index)` — walk to index, return data |
| **6h** | `src/LinkedList.cpp` | `contains(pos)` — walk list, check equality |

Then: update `Snake.hpp`/`Snake.cpp` to use `LinkedList` instead of `std::deque`.

---

## Phase 7: Architecture Diagram (Do Last)

| Step | File | What to do |
|------|------|------------|
| **7a** | `docs/architecture.md` | Draw module diagram showing relationships |

---

## Quick Reference: Start → Finish

```
START HERE
    │
    ▼
 1a → 1b → 1c  (LevelLoader)
    │
    ▼
 2a → 2b → 2c → 2d  (HighScoreManager)
    │
    ▼
 3a → 3b → 3c → 3d  (Menu)
    │
    ▼
 4a → 4b → 4c → 4d  (main.cpp wiring)
    │
    ▼
 5a → 5b  (Save scores in gameplay)
    │
    ▼
 6a → 6b → 6c → 6d → 6e → 6f → 6g → 6h  (LinkedList - Extra)
    │
    ▼
 7a  (Diagram - last)
    │
    ▼
  DONE ✅
```
