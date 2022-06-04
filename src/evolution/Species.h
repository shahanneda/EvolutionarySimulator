//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include "network/NetworkInstance.h"

#ifndef SPECIES_H
#define SPECIES_H


namespace NeatSquared {
    class Species {
        std::vector<std::reference_wrapper<NetworkInstance>> networks;
    };
}


#endif //SPECIES_H
