//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#include "NetworkBreeder.h"

#include <memory>
#include "NetworkInstance.h"
#include "utils/RandomGenerator.h"

using namespace NeatSquared;

const float NetworkBreeder::SAME_GENE_BOTH_PARENT_MORE_FIT_PROB = 0.5f;


const float NetworkBreeder::NEW_NEURON_MUTATION_PROB = 0.03f;
const float NetworkBreeder::NEW_CONNECTION_MUTATION_PROB = 0.05f;
const float NetworkBreeder::TOGGLE_CONNECTION_MUTATION_PROB = 0.1f;
const float NetworkBreeder::SCALE_WEIGHT_MUTATION_PROB = 0.4f;
const float NetworkBreeder::SET_WEIGHT_MUTATION_PROB = 0.8f;
const float NetworkBreeder::FLIP_CONNECTION_MUTATION_PROB = 0.1f;

const int NetworkBreeder::MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS = 5;

using std::vector;

NetworkBreeder::NetworkBreeder(NewGeneCreator &geneCreator) : geneCreator(geneCreator) {

}

std::unique_ptr<NetworkInstance> NetworkBreeder::breed(NetworkInstance &moreFitParent, NetworkInstance &lessFitParent) {
    auto network = crossover(moreFitParent, lessFitParent);
    mutateNetwork(*network);
    network->recalculateConnections();
    return network;
}


std::unique_ptr<NetworkInstance>
NetworkBreeder::crossover(NetworkInstance &moreFitParent, NetworkInstance &lessFitParent) {
    /*
     * for gene in moreFitParent, if it is also in the lessFitParent, pick one with 50/50 chance
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

    // use the same inputs /outputs as one of the parents, since those will never change
    auto network = std::make_unique<NetworkInstance>(newN, newC, moreFitParent.inputs, moreFitParent.outputs);
    return network;
}


void NetworkBreeder::mutateNetwork(NetworkInstance &network) {
    if (RandomGenerator::getRandom() < NEW_CONNECTION_MUTATION_PROB) {
        addNewConnectionMutation(network);
    }

    if (RandomGenerator::getRandom() < NEW_NEURON_MUTATION_PROB) {
        addNewNeuronMutation(network);
    }

    if (RandomGenerator::getRandom() < TOGGLE_CONNECTION_MUTATION_PROB) {
        toggleConnectionMutation(network);
    }

    if (RandomGenerator::getRandom() < SCALE_WEIGHT_MUTATION_PROB) {
        scaleWeightMutation(network);
    }

    if (RandomGenerator::getRandom() < SET_WEIGHT_MUTATION_PROB) {
        setWeightMutation(network);
    }

    if (RandomGenerator::getRandom() < FLIP_CONNECTION_MUTATION_PROB) {
        flipConnectionMutation(network);
    }
}

void NetworkBreeder::addNewNeuronMutation(NetworkInstance &network) {
    int attempts = 0;

    while (attempts < MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS) {
        Connection *c = network.getRandomConnection();
        if (!c) {
            attempts++;
            continue;
        }

        Neuron n = geneCreator.getNewNeuron();

        Connection from = geneCreator.getNewConnection(c->from, n.innovationNumber);
        from.weight = 1;
        from.enabled = true;

        Connection to = geneCreator.getNewConnection(n.innovationNumber, c->to);
        to.weight = c->weight;
        to.enabled = c->enabled;

        network.addNeuron(n);
        network.addConnection(from);
        network.addConnection(to);

        network.removeConnection(*c);
        break;
    }
}

void NetworkBreeder::addNewConnectionMutation(NetworkInstance &network) {
    int attempts = 0;

    // future considerations: maybe prevent two inputs or two outputs from forming a connection?
    // prevent backwards connections from forming?


    while (attempts < MAX_NEW_GENE_MUTATION_RETRY_ATTEMPTS) {
        Neuron *from = network.getRandomNeuron();
        Neuron *to = network.getRandomNeuron();

        //avoid bad connections for example, should not have connection starting from output, or connection going to inputs
        if (!from ||
            !to ||
            from->innovationNumber == to->innovationNumber ||
            network.isInnovationNumberOfInputNeuron(to->innovationNumber) ||
            network.isInnovationNumberOfOutputNeuron(from->innovationNumber)) {
            attempts++;
            continue;
        }


        Connection connectionBetweenThese = geneCreator.getNewConnection(from->innovationNumber,
                                                                         to->innovationNumber);
        connectionBetweenThese.weight = RandomGenerator::getRandomInRange(-2, 2);

        // maybe this connection is already in the network, in that case we should retry with two new nodes
        if (network.innovationToConnectionMap.count(connectionBetweenThese.innovationNumber) > 0) {
            attempts++;
        } else {
            network.addConnection(connectionBetweenThese);
            // stop trying to add connection
            break;
        }
    }
}

void NetworkBreeder::toggleConnectionMutation(NetworkInstance &network) {
    Connection *c = network.getRandomConnection();
    if (c) {
        c->enabled = !c->enabled;
    }
}


void NetworkBreeder::scaleWeightMutation(NetworkInstance &network) {
    Connection *c = network.getRandomConnection();
    float scale = RandomGenerator::getRandomFloatInRange(-1, 1.5f);
    if (c) {
        c->weight *= scale;
    }
}

void NetworkBreeder::setWeightMutation(NetworkInstance &network) {
    Connection *c = network.getRandomConnection();
    float newW = RandomGenerator::getRandomFloatInRange(-2, 2);
    if (c) {
        c->weight = newW;
    }
}

void NetworkBreeder::flipConnectionMutation(NetworkInstance &network) {
    Connection *c = network.getRandomConnection();
    // we do not want to create invalid connections going into an input, or from and output, so do not flip in those cases
    if (c && !network.isInnovationNumberOfInputNeuron(c->from) &&
        !network.isInnovationNumberOfOutputNeuron(c->to)) {
        int old = c->from;
        c->from = c->to;
        c->to = old;
    }
}



