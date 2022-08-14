//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Game.h"

#include <array>

namespace NeatSquared {
    class SnakeGame : public Game {

    public:
        struct BoardPosition {
            int x;
            int y;
        };
        enum TileType {
            SNAKE,
            FOOD,
            EMPTY
        };

        /*
         * Advances game to next step, return true if snake is alive, false if snake is dead.
         */
        bool nextGameIteration();

        enum Direction {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };
    private:


        struct SnakeNode {
            BoardPosition pos;
            SnakeNode *prev;
        };


        void setBoardPos(BoardPosition pos, TileType type);

        /*
         * Resets all aspects of the game, including score, iterationCount, snake position, and board.
         */
        void resetGame();


        void generateFood();

        static bool isValidBoardPosition(BoardPosition pos);

        bool isValidSnakeBoardPosition(BoardPosition pos);

        int score = 0;
        int iterationCount = 0;
        int lastFoodIteration = 0;


        constexpr const static int maximumIterationWithoutFoodCutoff = 100;
        constexpr const static int slowGameDownDelay = 50;
        constexpr const static float fitnessTimeMultiplier = 2.f;
        constexpr const static float fitnessScoreMultiplier = 100.f;
        constexpr const static float fitnessSizeMultiplier = -0.001;

        // Used for detecting snakes stuck in a short cycle and killing them quickly to save time;
        BoardPosition lastBoardPosition = {0, 0};
        BoardPosition secondLastBoardPosition = {0, 0};


    public:


        SnakeGame();

        float evaluateNetwork(NetworkInstance &network) override;

        static const int BOARD_SIZE = 10;

        SnakeNode snakeHead{{4, 4}, nullptr};
        BoardPosition foodPosition;
        Direction headDirection;
        std::array<TileType, BOARD_SIZE * BOARD_SIZE> board;

        TileType getBoardPos(BoardPosition pos);

        bool isFacingCorrectDirection() const;

        BoardPosition moveOneStepInDirection(BoardPosition pos, Direction direction);

        Direction rotateDirectionRight(Direction dir) const;

        Direction rotateDirectionLeft(Direction dir) const;
    };

};

#endif //SNAKEGAME_H
