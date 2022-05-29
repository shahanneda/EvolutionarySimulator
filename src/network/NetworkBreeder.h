//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#ifndef NETWORKBREEDER_H
#define NETWORKBREEDER_H


#include <algorithm>
#include "NetworkInstance.h"
#include "network/NewGeneCreator.h"

namespace NeatSquared {
    class NetworkBreeder {
    public:
        NetworkBreeder();

        /*
         * Breeds two networks and produces a new child network.
         */
        std::unique_ptr<NetworkInstance> crossover(NetworkInstance &moreFitParent, NetworkInstance &lessFitParent);


    private:

        /*
         * Mutates a network
         */
        void mutateNetwork(NetworkInstance &network);

        void addNewConnectionMutation(NetworkInstance &n);

        void addNewNeuronMutation(NetworkInstance &n);


        void toggleConnectionMutation(NetworkInstance &network);

        void scaleWeightMutation(NetworkInstance &network);

        void setWeightMutation(NetworkInstance &network);

        void flipConnectionMutation(NetworkInstance &network);

        NewGeneCreator geneCreator;


        /*
         * Probability that a gene will come from the more fit parent if it is found on both parents;
         */
        static const float SAME_GENE_BOTH_PARENT_MORE_FIT_PROB;

        /*
         * Probability that a new neuron will be added
         */
        static const float NEW_NEURON_MUTATION_PROB;

        /*
         * Probability that a new connection will be added;
         */
        static const float NEW_CONNECTION_MUTATION_PROB;


        /*
         * Probabilities for various mutations
         */
        static const float TOGGLE_CONNECTION_MUTATION_PROB;
        static const float SCALE_WEIGHT_MUTATION_PROB;
        static const float SET_WEIGHT_MUTATION_PROB;
        static const float FLIP_CONNECTION_MUTATION_PROB;

        /*
         * Number of times an add new connection/neuron mutation will attempt to make before giving up.
         */
        static const int MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS;

    };
}


#endif //NETWORKBREEDER_H
