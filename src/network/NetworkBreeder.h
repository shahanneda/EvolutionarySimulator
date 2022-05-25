//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#ifndef NETWORKBREEDER_H
#define NETWORKBREEDER_H


#include <algorithm>
#include "NetworkInstance.h"

namespace NeatSquared{
    class NetworkBreeder {
        /*
         * Breeds two networks and produces a new child network.
         */
        static std::unique_ptr<NetworkInstance> Crossover(NetworkInstance* network1, NetworkInstance* network2, float n1Fitness, float n2Fitness);

        /*
         * Mutates a network
         */
        static NetworkInstance* MutateNetwork(NetworkInstance* network);


    };
}


#endif //NETWORKBREEDER_H
