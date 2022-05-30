#include "Neuron.h"
#include "Connection.h"
#include "NetworkInstance.h"

#include <cmath>
#include <iostream>


using namespace NeatSquared;

Neuron::Neuron(int innovationNumber) : Gene(innovationNumber), currentValue(0) {}

/*
 * The way I have decided to handle cycles, is that once this recursive calculation reaches a loop, it just stops evaluating, and uses the default value of that loop, which starts
 * out at 0. However, the next time the network is evaluating, it will use the value from the last iteration, thus it will approximate a loop without actually having to do a loop.
 */
void Neuron::calculateValue(NetworkInstance &network) {
    float val = 0;
    if (network.alreadyVisitedNeuronInnovationNumbersWhenEvaluating.count(this->innovationNumber) != 0 ||
        network.isInnovationNumberOfInputNeuron(this->innovationNumber)) {
        return;
    }


    for (int conInnovationNumber: this->incomingConnections) {
        Connection *c = network.getConnectionWithInnovationNumber(conInnovationNumber);
        if (!c->enabled) {
            continue;
        }

        if (c->to != this->innovationNumber) {
            throw std::runtime_error(
                    " INVALID INCOMING CONNECTION WHEN EVALUATING NETWORK!! Have you called network.recalculateConnections()??");
        }

        Neuron *neuron = network.getNeuronWithInnovationNumber(c->from);

        if (!neuron) {
            throw std::runtime_error(
                    "NEURON NOT FOUND IN NETWORK, INVALID CONNECTION WHEN EVALUATING NETWORK!! Have you called network.recalculateConnections()??");
        }

        // store seen for dfs
        network.alreadyVisitedNeuronInnovationNumbersWhenEvaluating.insert({this->innovationNumber});
        neuron->calculateValue(network);

        float increment = neuron->currentValue * c->weight;
        val += increment;
        c->lastCalculatedValue = increment;
    }


    currentValue = activationFunction(val);
}

float Neuron::activationFunction(float input) {
    return input / (1 + abs(input));
}


void Neuron::removeConnection(Connection *con) {
    if (this->innovationNumber == con->from) {
        auto i = std::find(incomingConnections.begin(), incomingConnections.end(), con->innovationNumber);
        if (i != incomingConnections.end())
            incomingConnections.erase(i);
    } else if (this->innovationNumber == con->to) {
        auto i = std::find(outgoingConnections.begin(), outgoingConnections.end(), con->innovationNumber);
        if (i != outgoingConnections.end())
            outgoingConnections.erase(i);
    } else {
        throw std::runtime_error("Trying to remove connection from neuron which does not include neuron! ");
    }
}

void Neuron::addConnection(Connection *con) {
    if (this->innovationNumber == con->from) {
        this->outgoingConnections.push_back(con->innovationNumber);
    } else if (this->innovationNumber == con->to) {
        this->incomingConnections.push_back(con->innovationNumber);
    } else {
        throw std::runtime_error("Trying to add connection to neuron which does not include neuron! ");
    }
}
