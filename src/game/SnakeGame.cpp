//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#include "SnakeGame.h"

using namespace NeatSquared;

SnakeGame::SnakeGame() {
    this->numberOfInputs = 3;
    this->numberOfOutputs = 4;
}

SnakeGame::TileType SnakeGame::getBoardPos(BoardPosition pos) {
    if (!isValidBoardPosition(pos)) {
        throw std::runtime_error("Trying to get invalid board position!!");
    }

    return board[pos.x * BOARD_SIZE + pos.y];
}

void SnakeGame::setBoardPos(BoardPosition pos, SnakeGame::TileType type) {
    if (!isValidBoardPosition(pos)) {
        throw std::runtime_error("Trying to set invalid board position!!");
    }
    board[pos.x * BOARD_SIZE + pos.y] = type;
}


void SnakeGame::resetGame() {
    BoardPosition snakeStartingPosition = {4, 4};

    board.fill(SnakeGame::TileType::EMPTY);

    // free old snake
    SnakeNode *node = snakeHead.prev;
    while (node != nullptr) {
        SnakeNode *temp = node->prev;
        delete node;
        node = temp;
    }

    snakeHead = {snakeStartingPosition, nullptr};
    score = 0;
    iterationCount = 0;

}

float SnakeGame::evaluateNetwork(NetworkInstance &network) {
    return 0;
}

bool SnakeGame::nextGameIteration() {
    iterationCount += 1;

    BoardPosition oldPosition = snakeHead.pos;
    bool hasAte = false;

    // move head forward
    switch (headDirection) {
        case UP:
            snakeHead.pos = {snakeHead.pos.x, snakeHead.pos.y + 1};
            break;
        case DOWN:
            snakeHead.pos = {snakeHead.pos.x, snakeHead.pos.y - 1};
            break;
        case RIGHT:
            snakeHead.pos = {snakeHead.pos.x + 1, snakeHead.pos.y};
            break;
        case LEFT:
            snakeHead.pos = {snakeHead.pos.x - 1, snakeHead.pos.y};
            break;
    }
    if (!isValidSnakeBoardPosition(snakeHead.pos)) {
        // snake has died;
        return false;
    }
    if (getBoardPos(snakeHead.pos) == FOOD) {
        hasAte = true;
    }

    // TODO: add to the back of the snake here
    setBoardPos(oldPosition, EMPTY);
    setBoardPos(snakeHead.pos, SNAKE);

    // move rest of snake to follow
    SnakeNode *current = snakeHead.prev;
    while (current != nullptr) {
        BoardPosition temp = current->pos;
        current->pos = oldPosition;
        setBoardPos(current->pos, EMPTY);
        setBoardPos(oldPosition, SNAKE);
        oldPosition = temp;

        // preserve tail so we can add to it fast if needed
        if (current->prev) {
            current = current->prev;
        } else {
            break;
        }
    }

    if (hasAte) {
        current->prev = new SnakeNode({oldPosition, nullptr});
    }
    return true;
}

bool SnakeGame::isValidSnakeBoardPosition(SnakeGame::BoardPosition pos) {
    return isValidBoardPosition(pos) && getBoardPos(pos) != SNAKE;
}

bool SnakeGame::isValidBoardPosition(SnakeGame::BoardPosition pos) {
    return (pos.x < BOARD_SIZE && pos.y < BOARD_SIZE && pos.x >= 0 && pos.y >= 0);
}



