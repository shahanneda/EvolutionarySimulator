//
// Created by Shahan Nedadahandeh on 2022-05-30.
//

#include "network/NetworkInstance.h"

#include <vector>


#ifndef GAME_H
#define GAME_H


namespace NeatSquared {
    /*
     *
     * The game class is the interface for the network breeding manager to communicate with various games. Games inherit from this class, and they need to implement the following in order for the network breeding manager to be able to use them to train networks
     *
     *
     */
    class Game {

    public:
        /*
         * The number of inputs and outputs should be set in by the individual game classes and are used by the network breeding manager to construct networks of the right size.
         */
        int numberOfInputs = 0;
        int numberOfOutputs = 0;

        /*
         * Uses network to evaluate a game
         */
        virtual
        float EvaluateNetwork(NetworkInstance &network) = 0;

    };
}


#endif //GAME_H
