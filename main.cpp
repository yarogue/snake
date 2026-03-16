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
#include <cstdlib>
#include <ctime>


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

int handleInput(const char key, const int currentDirection) {
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
void moveSnake(std::vector<pos>& snake, const int snakeDirection) {

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

// ======================COLLISION=============================

bool isWall(const int x, const int y, const std::string& level, const int levelWidth) {
    const int index = y * levelWidth + x;
    return level[index] == '#';
}

bool isCollidingWithSelf(const std::vector<pos> &snake)  {
    auto [x, y] = snake[0];
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return true;
        }
    }
    return false;
}
// ============================================================

// ====================FOOD & GROWING==========================

pos spawnFood(const std::string& level,const int levelWidth,const int levelHeight,std::vector<pos>& snake)
{
    pos food{};
    bool isValid;
    do{
        food.x = rand() %  levelWidth;
        food.y = rand() % levelHeight;
        isValid = !isWall(food.x, food.y, level, levelWidth);
            for (const auto& [x, y] : snake)
            {
                if (x == food.x && y == food.y) isValid = false;
            }
    }while (!isValid);

    return food;
}

// ============================================================

// ======================GAME_LOOP=============================

// Game loop helpers

//Screen cleaning
void clearScreen() {
        std::cout << "\033[2J\033[H";
}

void sleepMs(const int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

char gameOver(int score)
{
    clearScreen();

    std::cout << "\033[" << "GAME_OVER" << std::endl;

    char key;
    do
    {
        key = getKeyPress();
    }while (key != 'r' && key != 'q');

    return key;
}

void gameLoop(std::vector<pos>& snake,int snakeDirection ,
    const std::string& level, const int levelWidth, const int levelHeight) {
    bool isRunning = true;
    int score = 0;

    pos food = spawnFood(level, levelWidth, levelHeight, snake);

    while (isRunning == true) {
        //Input
        const char key = getKeyPress();
        if (key == 'q' || key == 'Q') break;
        //Update direction
        snakeDirection = handleInput(key, snakeDirection);
        //Move
        moveSnake(snake, snakeDirection);
        //Draw and eat food
        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            snake.push_back(snake.back());
            food = spawnFood(level, levelWidth, levelHeight, snake);
        }
        //Collision (only here, AFTER move)
        if (auto [x, y] = snake[0]; isWall(x, y, level, levelWidth)) break;
        if (isCollidingWithSelf(snake)) break;
        //Draw
        clearScreen();
        drawLevel(level, levelWidth, levelHeight);
        drawTile(food.x, food.y, '*');
        drawSnake(snake);
        std::cout << "\033[" << (levelHeight + 1) << ";1H" << "Score:" << score;
        sleepMs(200);
    }

    char choice = gameOver(score);
}

// ============================================================

// =========================MAIN===============================

int main(const int argc, char* argv[]) {

    srand(time(nullptr));

    std::cout << "Arguments: " << argc << std::endl;

    for (int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;

    }
    const std::string level   = "########"
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

    constexpr int snakeDirection = RIGHT;
    enableRawMode();
    gameLoop(snake, snakeDirection, level, levelWidth, levelHeight);

    disableRawMode();

    // Move cursor below grid
    std::cout << "\033[" << (levelHeight + 1) << ";1H";

    return 0;

}