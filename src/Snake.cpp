#include "Snake.hpp"

void Snake::Move() {
    Position newHead = getHead() +
    DirectionUtils::toOffset(currentDirection);
    body.push_front(newHead);
    body.pop_back();
}

void Snake::Grow(){
    Position newHead = getHead() +
    DirectionUtils::toOffset(currentDirection);
    body.push_front(newHead);
}

Position Snake::getHead() const {
    return body.front();
}


bool Snake::isCollidingWithSelf() const {
    Position head = getHead();
    for(size_t i = 1; i < body.size(); ++i){
        if(body[i] == head){
            return true;
        }
    }
    return false;
}

void Snake::setDirection(Direction newDir){
    bool isIllegalTurn = false;

    switch(currentDirection){
        case Direction::UP:
            if(newDir == Direction::DOWN){
                isIllegalTurn = true;}
        break;
        case Direction::DOWN:
            if(newDir == Direction::UP){
            isIllegalTurn = true;}
        break;
        case Direction::LEFT:
            if(newDir == Direction::RIGHT){
            isIllegalTurn = true;}
        break;
        case Direction::RIGHT:
            if(newDir == Direction::LEFT){
            isIllegalTurn = true;}
        break;
    }
    if(!isIllegalTurn){
        currentDirection = newDir;
    }
}

Snake Snake::create(Position startPosition, Direction startDirection, int initialLength){
    Snake snake;

    snake.currentDirection = startDirection;

    Position offset = DirectionUtils::toOffset(startDirection);
    Position oppositeOffset = Position{-offset.x, -offset.y};

    for(int i = 0; i < initialLength; ++i){
    Position bodyPos = startPosition;
    bodyPos.x += i * oppositeOffset.x;
    bodyPos.y += i * oppositeOffset.y;

    snake.body.push_back(bodyPos);

    }
    return snake;
}