//
// Created by Shahan Nedadahandeh on 2022-06-03.
//

#include <string>

#include "Generation.h"

using namespace NeatSquared;

Generation::Generation(int id) : id(id) {}

NetworkInstance *Generation::getNetworkWithId(int id) {
    if (id >= size()) {
        throw std::runtime_error(
                "Trying to get network " + std::to_string(id) + " in generation " + std::to_string(this->id) +
                " which does not exist in generation!!");
    }

    return at(id).get();
}

void Generation::addNetwork(std::unique_ptr<NetworkInstance> &network) {
    push_back(std::move(network));
    NetworkInstance &storedNetwork = *at(size() - 1);
    storedNetwork.id = size() - 1;

    placeNetworkInSpecies(storedNetwork);
}

void Generation::placeNetworkInSpecies(NetworkInstance &network) {
    for (unsigned long i = 0; i < species.size(); i++) {
        if (species[i].getRepresentative().isCompatibleWith(network)) {
            species[i].addNetwork(network);
            return;
        }
    }

    // network was not compatible with any of the existing species, thus make a new species
    species.emplace_back(species.size());
    species[species.size() - 1].addNetwork(network);
}

