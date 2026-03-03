#pragma once

struct Position {
    int x;// column
    int y;// row

    bool operator==(const Position& other) const {
        return(x == other.x ) && (y == other.y);
    }

    Position operator+(const Position& other) const {
        Position result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
};

// ============================================================
// TODO 1a — Position struct
// ============================================================
// A Position is just a point on the 2D grid.
// It is used everywhere: snake body cells, food, obstacles, etc.
//
// MEMBERS to add:
//   int x;   // column
//   int y;   // row
//

// METHODS to implement inside the struct:
//
//   1. operator==(const Position& other) const
//      → return true if both x and y are equal to other.x and other.y
//
//   2. operator+(const Position& other) const
//      → return a NEW Position whose x = this->x + other.x
//                                    y = this->y + other.y
//      (This will be very handy when you move the snake head
//       by adding a direction offset to the current head position.)
//
// HINT: structs in C++ can have methods and operator overloads,
//       just like classes. Everything is public by default.
// ============================================================