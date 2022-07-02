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
        enum DIRECTION {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        struct BoardPosition {
            int x;
            int y;
        };

        enum TILE_TYPE {
            SNAKE,
            FOOD,
            EMPTY
        };

        struct SnakeNode {
            BoardPosition pos;
            SnakeNode *prev;
        };


        void setBoardPos(BoardPosition pos, TILE_TYPE type);

        /*
         * Resets all aspects of the game, including score, iterationCount, snake position, and board.
         */
        void resetGame();

        /*
         * Advances game to next step, return true if snake is alive, false if snake is dead.
         */
        bool nextGameIteration();

        int score = 0;
        int iterationCount = 0;
    public:

        SnakeGame();

        float evaluateNetwork(NetworkInstance &network) override;

        static const int BOARD_SIZE = 10;

        SnakeNode snakeHead{{4, 4}, nullptr};
        std::array<TILE_TYPE, BOARD_SIZE * BOARD_SIZE> board;

        TILE_TYPE getBoardPos(BoardPosition pos);


    }


#endif //SNAKEGAME_H
