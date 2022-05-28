//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#ifndef NETWORKBREEDER_H
#define NETWORKBREEDER_H


#include <algorithm>
#include "NetworkInstance.h"

namespace NeatSquared{
    class NetworkBreeder {
    public:
        /*
         * Breeds two networks and produces a new child network.
         */
        static std::unique_ptr<NetworkInstance> Crossover(NetworkInstance& moreFitParent, NetworkInstance& lessFitParent);





        /*
         * Mutates a network
         */
        void MutateNetwork(NetworkInstance& network);



    private:
        /*
         * Probablity that a gene will come from the more fit parent if it is found on both parents;
         */
        static const float SAME_GENE_BOTH_PARENT_MORE_FIT_PROB;

    };
}


#endif //NETWORKBREEDER_H
