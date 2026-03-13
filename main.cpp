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
#include <bits/fs_fwd.h>

//Position struct
struct pos {
    int x;
    int y;
};

void drawTile(const int x, const int y, const char character) {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H" << character;
}

void drawLevel(std::string level, int levelWidth, int levelHeight) {

    for (int y = 0; y < levelHeight; y++) {
        for (int x = 0; x < levelWidth; x++) {
            drawTile(x, y, level[y * levelWidth + x]);
        }
    }
}

//Main
int main(const int argc, char* argv[]) {
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
    // Clear screen and draw
    std::cout << "\033[2J\033[H";
    drawLevel(level, levelWidth, levelHeight);
    return 0;
}