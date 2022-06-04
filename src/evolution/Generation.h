//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include <unordered_map>
#include <vector>
#include <algorithm>

#include "network/NetworkInstance.h"


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


        // Allow outside to access these iterators so they can easily loop through the networks;
        using container::begin;
        using container::end;

        NetworkInstance *getNetworkWithId(int id);

        void addNetwork(std::unique_ptr<NetworkInstance> network);

        int id;

    };

}

#endif //GENERATION_H
