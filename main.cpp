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
// =========================SNAKE==============================

//Snake position enum
enum Direction { UP, DOWN, LEFT, RIGHT };

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

// =========================MAIN===============================
int main(const int argc, char* argv[]) {


    std::cout << "Arguments: " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    // Level data
    const std::string level = "########"
                              "#......#"
                              "#......#"
                              "#......#"
                              "#......#"
                              "#......#"
                              "#......#"
                              "########";

    //Creating level
    constexpr int levelWidth  = 8;
    constexpr int levelHeight = 8;

    //Creating snake
    std::vector<pos> snake;
    snake.push_back(pos{3, 3});
    snake.push_back(pos{2, 3});
    snake.push_back(pos{1, 3});

    //Clear screen
    std::cout << "\033[2J\033[H";

    //Drawing level
    drawLevel(level, levelWidth, levelHeight);

    //Drawing snake
    drawSnake(snake);

    //Move cursor
    std::cout << "\033[" << (levelHeight + 1) << ";1H";

    return 0;
}