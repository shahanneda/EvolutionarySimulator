//
// Created by Shahan Nedadahandeh on 2022-05-31.
//

#include "BreedingManager.h"
#include "network/Neuron.h"
#include "network/Connection.h"

#include <algorithm>
#include <memory>

using namespace NeatSquared;

const float BreedingManager::NETWORK_COMPATIBILITY_MATCHING_GENE_CONSTANT = 1;
const float BreedingManager::NETWORK_COMPATIBILITY_WEIGHT_DIFFERENCE_CONSTANT = 1;
const float BreedingManager::SAME_SPECIES_NETWORK_COMPATIBILITY_CUTOFF = 3;
const int BreedingManager::MAX_NETWORKS_IN_GENERATION = 10;

BreedingManager::BreedingManager(Game &game) : game(game), geneCreator(), networkBreeder(geneCreator) {
    createStartingGeneration();
}

void BreedingManager::createStartingGeneration() {
    generations.push_back(Generation(0));

    Generation &gen = generations[0];

    std::vector<Neuron> neurons;
    std::vector<int> inputNumbers;
    std::vector<int> outputNumbers;

    for (int i = 0; i < game.numberOfInputs; i++) {
        Neuron n = geneCreator.getNewNeuron();
        neurons.push_back(n);
        inputNumbers.push_back(n.innovationNumber);
    }
    for (int i = 0; i < game.numberOfOutputs; i++) {
        Neuron n = geneCreator.getNewNeuron();
        neurons.push_back(n);
        outputNumbers.push_back(n.innovationNumber);
    }

    for (int i = 0; i < MAX_NETWORKS_IN_GENERATION; i++) {
        std::unique_ptr<NetworkInstance> network(new NetworkInstance(neurons, {}, inputNumbers, outputNumbers));
        gen.addNetwork(network);
    }
}




