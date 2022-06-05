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
const float BreedingManager::SAME_SPECIES_NETWORK_COMPATIBILITY_CUTOFF = 0.5;
const int BreedingManager::MAX_NETWORKS_IN_GENERATION = 100;

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
        gen.addNetwork(
                std::make_unique<NetworkInstance>(neurons, std::vector<Connection>(), inputNumbers, outputNumbers));
    }
}


void BreedingManager::evaluateFitnessOfSpecies(Species &species) {
    float averageFitness = 0;

    for (NetworkInstance &network: species.networks) {
        network.lastEvaluationFitness = game.evaluateNetwork(network);
        averageFitness += network.lastEvaluationFitness;
    }
    species.averageFitness = averageFitness;

    std::sort(species.networks.begin(), species.networks.end(),
              [](const NetworkInstance &n1, const NetworkInstance &n2) {
                  return n1.lastEvaluationFitness > n2.lastEvaluationFitness;
              });
}

void BreedingManager::evaluateFitnessOfGeneration(Generation &generation) {
    for (Species &s: generation.species) {
        evaluateFitnessOfSpecies(s);
    }
}

int BreedingManager::getCurrentGenerationNumber() {
    return generations.size() - 1;
}

Generation &BreedingManager::getCurrentGeneration() {
    return generations[getCurrentGenerationNumber()];
}


void BreedingManager::breedNextGeneration() {
    int currentGenerationNumber = getCurrentGenerationNumber();

    generations.emplace_back(currentGenerationNumber + 1);

    Generation &oldGeneration = generations[currentGenerationNumber];
    Generation &newGeneration = generations[currentGenerationNumber + 1];

    float sumOfAverageSpeciesFitnessInGeneration = oldGeneration.getSumOfAverageSpeciesFitness();

    for (Species &s: oldGeneration.species) {
        int numberOfSurvivingNetworksInSpecies = (int)
                ((s.averageFitness / sumOfAverageSpeciesFitnessInGeneration) *
                 MAX_NETWORKS_IN_GENERATION);


        if (s.networks.empty()) {
            continue;
        }

        if (s.networks.size() == 1) {
            NetworkInstance &network = s.networks[0];
            NetworkInstance &randomNet = oldGeneration.getRandomNetwork();


            if (network.lastEvaluationFitness > randomNet.lastEvaluationFitness) {
                newGeneration.addNetwork(networkBreeder.breed(network, randomNet));
            } else {
                newGeneration.addNetwork(networkBreeder.breed(randomNet, network));
            }
            continue;
        }

        int currentlyBreedingMember = 0;
        for (int i = 0; i < numberOfSurvivingNetworksInSpecies; i++) {
            // if we reach the end of the species, go back and make more children from the start, the randomness in the process will mean children from the same parent won't be identical
            if (currentlyBreedingMember + 1 >= static_cast<int>(s.networks.size())) {
                currentlyBreedingMember = 0;
            }

            NetworkInstance &net1 = s.networks[currentlyBreedingMember];
            NetworkInstance &net2 = s.networks[currentlyBreedingMember + 1];

            if (net1.lastEvaluationFitness > net2.lastEvaluationFitness) {
                newGeneration.addNetwork(networkBreeder.breed(net1, net2));
            } else {
                newGeneration.addNetwork(networkBreeder.breed(net2, net1));
            }

            currentlyBreedingMember++;
        }

    }
}




