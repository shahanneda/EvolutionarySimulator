//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#include "SnakeGame.h"

#include <thread>
#include <chrono>

#include "utils/RandomGenerator.h"


using namespace NeatSquared;

SnakeGame::SnakeGame() {
    this->numberOfInputs = 6;
    this->numberOfOutputs = 2;
//    this->shouldSlowGame = true;

    resetGame();
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
    BoardPosition foodStartingPosition = {2, 2};

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
    lastFoodIteration = 0;


    generateFood();
}

float SnakeGame::evaluateNetwork(NetworkInstance &network) {
    resetGame();

    while (nextGameIteration()) {


        Neuron *const inputFoodHorizontal = network.getNeuronWithInnovationNumber(network.inputs[0]);
        Neuron *const inputFoodVertical = network.getNeuronWithInnovationNumber(network.inputs[1]);

        Neuron *const inputIsValidBlockUp = network.getNeuronWithInnovationNumber(network.inputs[2]);
        Neuron *const inputIsValidBlockRight = network.getNeuronWithInnovationNumber(network.inputs[3]);
        Neuron *const inputIsValidBlockLeft = network.getNeuronWithInnovationNumber(network.inputs[4]);
        Neuron *const inputIsValidBlockDown = network.getNeuronWithInnovationNumber(network.inputs[5]);

        // what about telling it if it needs to right right left up down

        Neuron *const outHorizontal = network.getNeuronWithInnovationNumber(network.outputs[0]);
        Neuron *const outVertical = network.getNeuronWithInnovationNumber(network.outputs[1]);
        inputIsValidBlockUp->currentValue = isValidSnakeBoardPosition(
                moveOneStepInDirection(snakeHead.pos, UP));
        inputIsValidBlockRight->currentValue = isValidSnakeBoardPosition(
                moveOneStepInDirection(snakeHead.pos, RIGHT));
        inputIsValidBlockLeft->currentValue = isValidSnakeBoardPosition(
                moveOneStepInDirection(snakeHead.pos, LEFT));
        inputIsValidBlockDown->currentValue = isValidSnakeBoardPosition(
                moveOneStepInDirection(snakeHead.pos, DOWN));


        inputFoodHorizontal->currentValue = (snakeHead.pos.x - foodPosition.x) > 0 ? 1 : -1;
        inputFoodVertical->currentValue = (snakeHead.pos.y - foodPosition.y) > 0 ? 1 : -1;

        network.evaluateNetwork();

        if (outHorizontal->currentValue >= 0.5f) {
            headDirection = LEFT;
        }
        if (outHorizontal->currentValue <= -0.5f) {
            headDirection = RIGHT;
        }
        if (outVertical->currentValue >= 0.5f) {
            headDirection = UP;
        }
        if (outVertical->currentValue <= -0.5f) {
            headDirection = DOWN;
        }

        if (shouldSlowGame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SnakeGame::slowGameDownDelay));
        }
    }

    float sizeModifier = network.getSize() * 0.001f;


    return iterationCount * fitnessTimeMultiplier + score * fitnessScoreMultiplier - sizeModifier;
}

SnakeGame::Direction SnakeGame::rotateDirectionRight(SnakeGame::Direction dir) const {
    switch (dir) {
        case RIGHT:
            return DOWN;
        case LEFT:
            return UP;
        case UP:
            return RIGHT;
        case DOWN:
            return LEFT;
    }
}

SnakeGame::Direction SnakeGame::rotateDirectionLeft(SnakeGame::Direction dir) const {
    switch (dir) {
        case RIGHT:
            return UP;
        case LEFT:
            return DOWN;
        case UP:
            return LEFT;
        case DOWN:
            return RIGHT;
    }
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
            return {pos.x, pos.y - 1};
        case DOWN:
            return {pos.x, pos.y + 1};
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
    SnakeNode *prev = &snakeHead;
    SnakeNode *current = snakeHead.prev;
    while (current != nullptr) {
        BoardPosition temp = current->pos;

        setBoardPos(current->pos, EMPTY); // empty the spot for this node

        current->pos = oldPosition; //set this nodes position where the one ahead of it previously was
        setBoardPos(current->pos, SNAKE); // color this node

        oldPosition = temp; // store the nodes old position for other nodes

        // go to next node
        prev = current;
        current = prev->prev;
    }

    // add new node if has ate
    if (hasAte) {
        lastFoodIteration = iterationCount;
        score++;
        // oldPosition holds the old spot of the last node, so where the new snake node should go
        prev->prev = new SnakeNode({oldPosition, nullptr});
        generateFood();
    }

    if (iterationCount - lastFoodIteration > maximumIterationWithoutFoodCutoff) {
        // kill snake if it hasnt ate food in a while
        return false;
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
    do {
        foodPosition = {RandomGenerator::getRandomInRange(0, BOARD_SIZE - 1),
                        RandomGenerator::getRandomInRange(0, BOARD_SIZE - 1)};

    } while (getBoardPos(foodPosition) == SNAKE);

    setBoardPos(foodPosition, FOOD);
}



