//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#include "NetworkBreeder.h"
#include "NetworkInstance.h"
#include "utils/RandomGenerator.h"

using namespace NeatSquared;

const float NetworkBreeder::SAME_GENE_BOTH_PARENT_MORE_FIT_PROB = 0.5f;


// after the initial testing these two should be pretty low
const float NetworkBreeder::NEW_NEURON_MUTATION_PROB = 0.5f;
const float NetworkBreeder::NEW_CONNECTION_MUTATION_PROB = 1.f;
const int NetworkBreeder::MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS = 5;

using std::vector;

NetworkBreeder::NetworkBreeder() {

}


std::unique_ptr<NetworkInstance>
NetworkBreeder::crossover(NetworkInstance &moreFitParent, NetworkInstance &lessFitParent) {
    /*
     * for gene in moreFitParent, if it is also in the lessFitParent, do 50/50 chance
     * if it is not in lessFitParent, just add it to the current geonome
     */

    vector<Neuron> newN;
    vector<Connection> newC;

    for (const auto &it: moreFitParent.innovationToNeuronMap) {
        Neuron neuron = it.second;

        auto lessFitIt = lessFitParent.innovationToNeuronMap.find(neuron.innovationNumber);
        if (lessFitIt == lessFitParent.innovationToNeuronMap.end()) {
            // found on more fit parent only, keep
            newN.push_back(neuron);
        } else {
            // found on both, so randomly select one
            if (RandomGenerator::getRandom() < SAME_GENE_BOTH_PARENT_MORE_FIT_PROB) {
                newN.push_back(neuron);
            } else {
                newN.push_back(lessFitIt->second);
            }
        }
    }

    for (const auto &it: moreFitParent.innovationToConnectionMap) {
        Connection connection = it.second;

        auto lessFitIt = lessFitParent.innovationToConnectionMap.find(connection.innovationNumber);
        if (lessFitIt == lessFitParent.innovationToConnectionMap.end()) {
            // found on more fit parent only, keep
            newC.push_back(connection);
        } else {
            // found on both, so randomly select one
            if (RandomGenerator::getRandom() < SAME_GENE_BOTH_PARENT_MORE_FIT_PROB) {
                newC.push_back(connection);
            } else {
                newC.push_back(lessFitIt->second);
            }
        }
    }

    auto network = std::unique_ptr<NetworkInstance>(new NetworkInstance(newN, newC));
    mutateNetwork(*network);
    network->recalculateConnections();

    return network;
}


void NetworkBreeder::mutateNetwork(NetworkInstance &network) {
    if (RandomGenerator::getRandom() < NEW_CONNECTION_MUTATION_PROB) {
        addNewConnectionMutation(network);
    }

    if (RandomGenerator::getRandom() < NEW_NEURON_MUTATION_PROB) {
        addNewNeuronMutation(network);
    }
}

void NetworkBreeder::addNewNeuronMutation(NetworkInstance &network) {

}

void NetworkBreeder::addNewConnectionMutation(NetworkInstance &network) {
    int attempts = 0;

    // future considerations: maybe prevent two inputs or two outputs from forming a connection?
    // prevent backwards connections from forming?


    while (attempts < MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS) {
        Neuron &n1 = network.getRandomNeuron();
        Neuron &n2 = network.getRandomNeuron();

        if (n1.innovationNumber == n2.innovationNumber) {
            attempts++;
            continue;
        }


        Connection connectionBetweenThese = geneCreator.getNewConnection(n1.innovationNumber, n2.innovationNumber);

        // maybe this connection is already in the network, in that case we should retry with two new nodes
        printf("trying to add connection between %d and %d\n", n1.innovationNumber, n2.innovationNumber);

        if (network.innovationToConnectionMap.count(connectionBetweenThese.innovationNumber) > 0) {
            attempts++;
            printf("\tfailed\n");
        } else {
            network.addConnection(connectionBetweenThese);
            printf("\tadded\n");
            // stop trying to add connection
            break;
        }
    }
}



