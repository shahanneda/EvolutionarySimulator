//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include <unordered_map>
#include <vector>
#include <algorithm>

#include "network/NetworkInstance.h"
#include "evolution/Species.h"


#ifndef GENERATION_H
#define GENERATION_H

namespace NeatSquared {
/*
 * A generation is a container that stores the network instances of a particular generation
 */
    class Generation : private std::vector<std::unique_ptr<NetworkInstance>> {
        using container =
                std::vector<std::unique_ptr<NetworkInstance>>;
    public:
        explicit Generation(int id);

        NetworkInstance *getNetworkWithId(int id);

        void addNetwork(std::unique_ptr<NetworkInstance> network);

        /*
         * Returns the sum of the fitness of all the species, using each species average fitness.
         */
        float getSumOfAverageSpeciesFitness() const;


        NetworkInstance &getRandomNetwork();


        const int id;
        std::vector<Species> species;

        // Allow outside to access these iterators so they can easily loop through the networks;
        using container::begin;
        using container::end;

    private:
        void placeNetworkInSpecies(NetworkInstance &network);


    };

}

#endif //GENERATION_H
