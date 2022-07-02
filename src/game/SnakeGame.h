//
// Created by Shahan Nedadahandeh on 2022-07-01.
//

#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Game.h"

#include <array>

namespace NeatSquared {
    class SnakeGame : public Game {

    private:
        enum Direction {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        struct BoardPosition {
            int x;
            int y;
        };

        enum TileType {
            SNAKE,
            FOOD,
            EMPTY
        };

        struct SnakeNode {
            BoardPosition pos;
            SnakeNode *prev;
        };


        void setBoardPos(BoardPosition pos, TileType type);

        /*
         * Resets all aspects of the game, including score, iterationCount, snake position, and board.
         */
        void resetGame();

        /*
         * Advances game to next step, return true if snake is alive, false if snake is dead.
         */
        bool nextGameIteration();

        static bool isValidBoardPosition(BoardPosition pos);

        bool isValidSnakeBoardPosition(BoardPosition pos);

        int score = 0;
        int iterationCount = 0;

    public:
        SnakeGame();

        float evaluateNetwork(NetworkInstance &network) override;

        static const int BOARD_SIZE = 10;

        SnakeNode snakeHead{{4, 4}, nullptr};
        Direction headDirection;
        std::array<TileType, BOARD_SIZE * BOARD_SIZE> board;

        TileType getBoardPos(BoardPosition pos);
    }


#endif //SNAKEGAME_H
