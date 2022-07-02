//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#include "SnakeGame.h"

using namespace NeatSquared;

SnakeGame::SnakeGame() {
    this->numberOfInputs = 3;
    this->numberOfOutputs = 4;
}

SnakeGame::TILE_TYPE SnakeGame::getBoardPos(BoardPosition pos) {
    if (pos.x >= BOARD_SIZE || pos.y >= BOARD_SIZE || pos.x < 0 || pos.y < 0) {
        throw std::runtime_error("Trying to get invalid board position!!");
    }

    return board[pos.x * BOARD_SIZE + pos.y];
}

void SnakeGame::setBoardPos(BoardPosition pos, SnakeGame::TILE_TYPE type) {
    if (pos.x >= BOARD_SIZE || pos.y >= BOARD_SIZE || pos.x < 0 || pos.y < 0) {
        throw std::runtime_error("Trying to set invalid board position!!");
    }

    board[pos.x * BOARD_SIZE + pos.y] = type;
}

void SnakeGame::resetGame() {
    BoardPosition snakeStartingPosition = {4, 4};

    board.fill(SnakeGame::TILE_TYPE::EMPTY);

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
    return true;
}



