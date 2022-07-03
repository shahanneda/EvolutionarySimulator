//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#include "SnakeGame.h"

#include <thread>
#include <chrono>

#include "utils/RandomGenerator.h"


using namespace NeatSquared;

SnakeGame::SnakeGame() {
    this->numberOfInputs = 2;
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
    resetGame();

    while (nextGameIteration()) {
        Neuron *const inputIsFacingCorrectDirection = network.getNeuronWithInnovationNumber(network.inputs[0]);
        Neuron *const inputIsValidBlockInFront = network.getNeuronWithInnovationNumber(network.inputs[1]);

        Neuron *const outGoLeft = network.getNeuronWithInnovationNumber(network.outputs[0]);
        Neuron *const outGoRight = network.getNeuronWithInnovationNumber(network.outputs[1]);
        Neuron *const outGoUp = network.getNeuronWithInnovationNumber(network.outputs[2]);
        Neuron *const outGoDown = network.getNeuronWithInnovationNumber(network.outputs[3]);


        inputIsFacingCorrectDirection->currentValue = isFacingCorrectDirection();
        inputIsValidBlockInFront->currentValue = isValidSnakeBoardPosition(
                moveOneStepInDirection(snakeHead.pos, headDirection));

        if (outGoLeft->currentValue >= 0.5f) {
            headDirection = LEFT;
        }
        if (outGoRight->currentValue >= 0.5f) {
            headDirection = RIGHT;
        }
        if (outGoUp->currentValue >= 0.5f) {
            headDirection = UP;
        }
        if (outGoDown->currentValue >= 0.5f) {
            headDirection = UP;
        }
    }


    if (shouldSlowGame) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SnakeGame::slowGameDownDelay));
    }

    return iterationCount * fitnessTimeMultiplier + score * fitnessScoreMultiplier;
}

bool SnakeGame::isFacingCorrectDirection() const {
    switch (headDirection) {
        case RIGHT:
            return snakeHead.pos.x < foodPosition.x;
        case LEFT:
            return snakeHead.pos.x > foodPosition.x;
        case UP:
            return snakeHead.pos.y > foodPosition.y;
        case DOWN:
            return snakeHead.pos.y < foodPosition.y;
    }
}

SnakeGame::BoardPosition SnakeGame::moveOneStepInDirection(BoardPosition pos, Direction direction) {
    // move head forward
    switch (direction) {
        case UP:
            return {pos.x, pos.y + 1};
        case DOWN:
            return {pos.x, pos.y - 1};
        case RIGHT:
            return {pos.x + 1, pos.y};
        case LEFT:
            return {pos.x - 1, pos.y};
    }
}

bool SnakeGame::nextGameIteration() {
    iterationCount += 1;

    BoardPosition oldPosition = snakeHead.pos;
    bool hasAte = false;

    snakeHead.pos = moveOneStepInDirection(snakeHead.pos, headDirection);

    if (!isValidSnakeBoardPosition(snakeHead.pos)) {
        // snake has died;
        return false;
    }

    if (getBoardPos(snakeHead.pos) == FOOD) {
        hasAte = true;
    }

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

    // add new node if has ate
    if (hasAte) {
        score++;
        // oldPosition holds the old spot of the last node, so where the new snake node should go
        current->prev = new SnakeNode({oldPosition, nullptr});
        generateFood();
    }

    return true;
}

bool SnakeGame::isValidSnakeBoardPosition(SnakeGame::BoardPosition pos) {
    return isValidBoardPosition(pos) && getBoardPos(pos) != SNAKE;
}

bool SnakeGame::isValidBoardPosition(SnakeGame::BoardPosition pos) {
    return (pos.x < BOARD_SIZE && pos.y < BOARD_SIZE && pos.x >= 0 && pos.y >= 0);
}

void SnakeGame::generateFood() {
    foodPosition = {RandomGenerator::getRandomInRange(0, BOARD_SIZE - 1),
                    RandomGenerator::getRandomInRange(0, BOARD_SIZE - 1)};

    setBoardPos(foodPosition, FOOD);
}



