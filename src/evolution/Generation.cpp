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

void Generation::addNetwork(std::unique_ptr<NetworkInstance> network) {
    push_back(std::move(network));
    at(size() - 1)->id = size() - 1;
}

Generation::Generation(Generation &&other) : container(std::move(other)), id(other.id) {}

