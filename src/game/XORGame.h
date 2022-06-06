//
// Created by Shahan Nedadahandeh on 2022-05-30.
//

#include "game/Game.h"

#ifndef XORGAME_H
#define XORGAME_H


namespace NeatSquared {
    class XORGame : public Game {
    public:
        XORGame();

        float evaluateNetwork(NetworkInstance &network) override;

        /*
         * Returns a high number if actual is close to expected, returns a low number if actual is far from expected. Inspired by logistic regression loss function.
         */
        static float logisticFitness(float actual, int expected);

    private:
        const int numberOfIterations = 10;

        float differenceSquaredFitness(float actual, float expected);
    };
}


#endif //XORGAME_H
