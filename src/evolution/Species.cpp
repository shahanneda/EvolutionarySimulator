//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include "Species.h"

using namespace NeatSquared;

Species::Species(int id) : id(id) {

}


NetworkInstance &Species::getRepresentative() {
    if (networks.empty()) {
        throw std::runtime_error("Trying to get the representative of a species which has no networks!! ");
    }

    return networks[0];
}

void Species::addNetwork(NetworkInstance &network) {
    networks.push_back(network);
}

