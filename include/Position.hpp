#pragma once

struct Position {
    //Members
    int x;// column
    int y;// row

    //Methods
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