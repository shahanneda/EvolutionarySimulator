//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include "network/NetworkInstance.h"

#ifndef SPECIES_H
#define SPECIES_H


namespace NeatSquared {
    class Species {
    public:
        Species(int id);

        NetworkInstance &getRepresentative();

        void addNetwork(NetworkInstance &network);

        std::vector<std::reference_wrapper<NetworkInstance>> networks;
        const int id;

    };
}


#endif //SPECIES_H
