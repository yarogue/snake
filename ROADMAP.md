# 🐍 Snake Game — Learning Roadmap

> Follow these steps in order. Each step has pseudocode showing you what to write.  
> All code goes in **`main.cpp`**. Build with: `g++ -std=c++17 -o snake main.cpp`

---

## Step 1 — Foundations

### 1a. Command-line arguments
*Learn: `argc`, `argv`, for-loops, `std::cout`*

```
FUNCTION main(argc, argv):
    PRINT "Number of arguments: " argc
    FOR i FROM 0 TO argc:
        PRINT "argv[" i "]: " argv[i]
```

**Test:** `./snake hello world` → should print 3 arguments.

---

### 1b. The Position struct
*Learn: structs, member variables*

```
STRUCT pos:
    INT x
    INT y
```

Simply define this above `main()`.

---

### 1c. The level as a string
*Learn: `std::string`, multi-line string concatenation*

```
STRING level = "########"
               "#......#"
               "#......#"
               "#......#"
               "#......#"
               "########"

INT levelWidth  = 8
INT levelHeight = 6
```

Define these as variables inside `main()` (or as globals for now).

---

### 1d. Draw the level with a drawTile function
*Learn: functions, loops, `std::cout`, ANSI escape codes*

```
FUNCTION drawTile(x, y, character):
    // Move cursor to row y, column x using ANSI escape:
    // "\033[" + (y+1) + ";" + (x+1) + "H"
    PRINT escape_sequence + character

FUNCTION drawLevel(level, levelWidth):
    INT x = 0
    INT y = 0
    FOR i FROM 0 TO level.size():
        CHAR tile = level[i]
        drawTile(x, y, tile)
        x = x + 1
        IF x == levelWidth:
            x = 0
            y = y + 1
```

**Test:** call `drawLevel()` in main, run `./snake` → you should see the bordered grid.

> **Hint:** `"\033[2J"` clears the terminal screen. Print it before drawing.

---

## Step 2 — The Snake

### 2a. Snake data
*Learn: `std::vector`, storing structs in a vector*

```
// The snake body is a list of positions.
// Index 0 = head, last index = tail.
VECTOR<pos> snake
snake.push_back( pos{3, 2} )  // head
snake.push_back( pos{3, 3} )  // tail segment
```

---

### 2b. Draw the snake
*Learn: iterating over vectors, if-else*

```
FUNCTION drawSnake(snake):
    FOR i FROM 0 TO snake.size():
        IF i == 0:
            drawTile(snake[i].x, snake[i].y, '@')   // head
        ELSE:
            drawTile(snake[i].x, snake[i].y, 'o')   // body
```

**Test:** draw the level, then draw the snake on top → you should see `@o` inside the grid.

---

### 2c. Snake direction
*Learn: enums or simple int constants*

```
// Direction as integers:
INT DIR_UP    = 0
INT DIR_DOWN  = 1
INT DIR_LEFT  = 2
INT DIR_RIGHT = 3

INT snakeDirection = DIR_RIGHT
```

Or use an `enum` if you prefer:
```
ENUM Direction { UP, DOWN, LEFT, RIGHT }
```

---

### 2d. Moving the snake
*Learn: insert at front, remove from back, switch statements*

```
FUNCTION moveSnake(snake, direction):
    // 1. Figure out new head position
    pos head = snake[0]
    pos newHead = head

    SWITCH direction:
        CASE UP:    newHead.y = head.y - 1
        CASE DOWN:  newHead.y = head.y + 1
        CASE LEFT:  newHead.x = head.x - 1
        CASE RIGHT: newHead.x = head.x + 1

    // 2. Add new head to front
    snake.insert(snake.begin(), newHead)

    // 3. Remove tail (last element)
    snake.pop_back()
```

**Test:** call `moveSnake` a few times, draw after each call → snake should slide across the screen.

---

## Step 3 — Input

### 3a. Reading keyboard input (non-blocking)
*Learn: terminal raw mode, `read()`, `select()` (Linux system calls)*

```
// On Linux, we need "raw mode" to read keys without pressing Enter.
// This uses <termios.h> and <unistd.h> — they are part of the OS, not external libraries.

FUNCTION enableRawMode():
    GET current terminal settings
    TURN OFF canonical mode (line buffering)
    TURN OFF echo
    SET minimum chars to 0, timeout to 0
    APPLY new settings

FUNCTION disableRawMode():
    RESTORE original terminal settings

FUNCTION getKeyPress() -> CHAR:
    CHAR c = 0
    read(STDIN, &c, 1)     // reads 1 byte, returns immediately if nothing
    RETURN c
```

> **Hint:** Look up `struct termios`, `tcgetattr`, `tcsetattr` with `TCSAFLUSH`.

---

### 3b. Map keys to direction
*Learn: if-else chains, character comparisons*

```
FUNCTION handleInput(key, snakeDirection) -> INT:
    IF key == 'w' AND snakeDirection != DOWN:  RETURN UP
    IF key == 's' AND snakeDirection != UP:    RETURN DOWN
    IF key == 'a' AND snakeDirection != RIGHT: RETURN LEFT
    IF key == 'd' AND snakeDirection != LEFT:  RETURN RIGHT
    RETURN snakeDirection   // no change
```

Note the 180-degree turn prevention: you can't go UP if already going DOWN, etc.

---

## Step 4 — The Game Loop

### 4a. Basic loop with timing
*Learn: while-loops, `<chrono>`, `<thread>`, `usleep`*

```
FUNCTION gameLoop():
    BOOL running = true

    WHILE running:
        // 1. Read input
        CHAR key = getKeyPress()

        IF key == 'q':
            running = false
            CONTINUE

        // 2. Update direction
        snakeDirection = handleInput(key, snakeDirection)

        // 3. Move snake
        moveSnake(snake, snakeDirection)

        // 4. Check collisions (step 5 below)

        // 5. Draw everything
        clearScreen()
        drawLevel(level, levelWidth)
        drawSnake(snake)

        // 6. Wait (controls game speed)
        sleep_for(200 milliseconds)
```

**Test:** run the game, press WASD → snake should move around!

---

## Step 5 — Collision

### 5a. Wall collision
*Learn: checking values in a string by index*

```
FUNCTION isWall(x, y, level, levelWidth) -> BOOL:
    INT index = y * levelWidth + x
    RETURN level[index] == '#'
```

```
// In the game loop, after moving:
pos head = snake[0]
IF isWall(head.x, head.y, level, levelWidth):
    running = false
    PRINT "You hit a wall! Game Over."
```

---

### 5b. Self collision
*Learn: nested loops, comparing structs*

```
FUNCTION isCollidingWithSelf(snake) -> BOOL:
    pos head = snake[0]
    FOR i FROM 1 TO snake.size():
        IF snake[i].x == head.x AND snake[i].y == head.y:
            RETURN true
    RETURN false
```

---

## Step 6 — Food & Growing

### 6a. Spawn food randomly
*Learn: `srand`, `rand`, do-while for valid placement*

```
FUNCTION spawnFood(level, levelWidth, levelHeight, snake) -> pos:
    pos food
    DO:
        food.x = rand() % levelWidth
        food.y = rand() % levelHeight
    WHILE isWall(food.x, food.y, ...) OR isOnSnake(food, snake)
    RETURN food
```

Don't forget: `srand(time(nullptr))` once at the start of `main()`.

---

### 6b. Draw the food
```
drawTile(food.x, food.y, '*')
```

---

### 6c. Eating — grow the snake
*Learn: conditional logic in the game loop*

```
// In the game loop, AFTER moving but BEFORE popping the tail:
// (modify moveSnake or handle it in the loop)

IF head.x == food.x AND head.y == food.y:
    // Don't remove tail → snake grows by 1!
    // (skip the pop_back)
    score = score + 1
    food = spawnFood(...)
ELSE:
    snake.pop_back()   // normal move — remove tail
```

---

## Step 7 — Score & Game Over

### 7a. Display score
```
// After drawing the level, move cursor below the grid:
moveCursor(0, levelHeight + 1)
PRINT "Score: " score
```

---

### 7b. Game over screen
```
FUNCTION gameOver(score):
    clearScreen()
    PRINT "========= GAME OVER ========="
    PRINT "Final score: " score
    PRINT "Press 'r' to restart or 'q' to quit"

    CHAR key
    DO:
        key = getKeyPress()
    WHILE key != 'r' AND key != 'q'

    RETURN key
```

---

## Step 8 — Polish (optional extras)

### 8a. Zoom effect (from the requirements)
*Learn: scaling output*
```
// Instead of drawing 1 tile = 1 character, draw 1 tile = 2x2 characters:
FUNCTION drawTileZoomed(x, y, tile):
    drawTile(x*2,     y*2,     tile)
    drawTile(x*2 + 1, y*2,     tile)
    drawTile(x*2,     y*2 + 1, tile)
    drawTile(x*2 + 1, y*2 + 1, tile)
```

### 8b. Use `argc`/`argv` for options
```
// Example: ./snake --speed 100
// Parse argv to let the player choose game speed
```

---

## Quick Reference — Project Structure

```
snake/
├── main.cpp          ← everything goes here
├── CMakeLists.txt    ← simple: just compiles main.cpp
├── ROADMAP.md        ← this file (your guide)
└── .gitignore
```

## Build & Run

```bash
g++ -std=c++17 -o snake main.cpp && ./snake
```

Or with CMake:
```bash
mkdir -p build && cmake -S . -B build && cmake --build build && ./build/snake
```
