// ============================================================
// SNAKE GAME — Requirement-Fulfilling Version
// ============================================================
// Build:  g++ -std=c++17 -o snake main.cpp
// Run:    ./snake
// ============================================================
//
// Follow the ROADMAP.md for step-by-step instructions!
//
// This file is your blank canvas. Each TODO corresponds
// to a step in the roadmap.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


#ifdef _WIN32
    // Windows
    #include <conio.h>
    char getKeyPress() {
        if (_kbhit()) return _getch();
        return 0;
    }
void enableRawMode()  {}  // not needed on Windows, _getch handles it
void disableRawMode() {}
#else
// ============================================================
// Linux / macOS
#include <termios.h>
#include <unistd.h>

struct termios originalTermios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);
}

char getKeyPress() {
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    return c;
}
#endif


// ============================================================

// =========================SNAKE==============================

//Snake position enum
enum Direction { UP, DOWN, LEFT, RIGHT };

int handleInput(char key, int currentDirection) {
    if (key == 'w' && currentDirection != DOWN)  return UP;
    if (key == 's' && currentDirection != UP)    return DOWN;
    if (key == 'a' && currentDirection != RIGHT) return LEFT;
    if (key == 'd' && currentDirection != LEFT)  return RIGHT;
    return currentDirection;
}

//Snake data
struct pos {
    int x;
    int y;
};

//Outputting tiles for level and snake
void drawTile(const int x, const int y, const char character) {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H" << character;
}

//Drawing snake
void drawSnake(const std::vector<pos>& snake) {
    for (int i = 0; i < snake.size();i++) {
        if (i == 0) {
            drawTile(snake[i].x, snake[i].y, '@'); // head
        }
        else {
            drawTile(snake[i].x, snake[i].y, 'o'); // body
        }
    }
}

//Moving snake
void moveSnake(std::vector<pos>& snake, int snakeDirection) {

    const pos head = snake[0];
    auto [x, y] = head;

    switch (snakeDirection) {
        case UP:    y--; break;
        case DOWN:  y++; break;
        case LEFT:  x--; break;
        case RIGHT: x++; break;
    }

    snake.insert(snake.begin(), pos{x, y});  // new head
    snake.pop_back();                                  // removing tail
}

// ============================================================

// ========================LEVEL===============================

//Drawing level
void drawLevel(const std::string& level, const int levelWidth, const int levelHeight) {

    for (int y = 0; y < levelHeight; y++) {
        for (int x = 0; x < levelWidth; x++) {
            drawTile(x, y, level[y * levelWidth + x]);
        }
    }
}
// ============================================================

// ======================GAME_LOOP=============================

// Game loop helpers

//Screen cleaning
void clearScreen() {
        std::cout << "\033[2J\033[H";
}

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void gameLoop(std::vector<pos>& snake,int snakeDirection ,
    const std::string& level, const int levelWidth, const int levelHeight) {
    bool isRunning = true;

    while (isRunning == true) {
        //Reading input
        const char key = getKeyPress();

        //Exit
        if (key == 'q' || key == 'Q') {
            isRunning = false;
            break;
        }

        //Updating direction
        snakeDirection = handleInput(key, snakeDirection);

        //Moving snake
        moveSnake(snake, snakeDirection);

        //TODO: check for collision

        //Drawing everything
        clearScreen();
        drawLevel(level ,levelWidth, levelHeight);
        drawSnake(snake);
        sleepMs(200);

    }
}

// ============================================================

// =========================MAIN===============================
int main(const int argc, char* argv[]) {
        std::cout << "Arguments: " << argc << std::endl;
        for (int i = 0; i < argc; i++) {
            std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
        }
        const std::string level = "########"
                                  "#......#"
                                  "#......#"
                                  "#......#"
                                  "#......#"
                                  "#......#"
                                  "#......#"
                                  "########";
        constexpr int levelWidth  = 8;
        constexpr int levelHeight = 8;

        std::vector<pos> snake;

        snake.push_back(pos{3, 3});
        snake.push_back(pos{2, 3});
        snake.push_back(pos{1, 3});

        int snakeDirection = RIGHT;
        enableRawMode();   // ← turn on raw input before game
        gameLoop(snake, snakeDirection, level, levelWidth, levelHeight);

        disableRawMode();  // ← restore terminal after game

        // Move cursor below grid
        std::cout << "\033[" << (levelHeight + 1) << ";1H";

        return 0;
}