#include <algorithm>
#include "network/NetworkInstance.h"
#include <iostream>
#include "utils/RandomGenerator.h"

using namespace NeatSquared;

using std::pair;

std::vector<int> NetworkInstance::DEFAULT_INPUTS = {0, 1};
std::vector<int> NetworkInstance::DEFAULT_OUTPUTS = {2};


NetworkInstance::NetworkInstance(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                                 const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs,
                                 std::vector<int> outputs)
        : innovationToConnectionMap(
        innovationToConnectionMap), innovationToNeuronMap(innovationToNeuronMap), inputs(inputs), outputs(outputs) {}

NetworkInstance::NetworkInstance(const std::vector<Neuron> &neurons, const std::vector<Connection> &connections,
                                 std::vector<int> inputs, std::vector<int> outputs) : inputs(inputs), outputs(outputs) {
    for (auto c: connections) {
        innovationToConnectionMap.insert(pair<int, Connection>(c.innovationNumber, c));
    }
    for (auto n: neurons) {
        innovationToNeuronMap.insert(pair<int, Neuron>(n.innovationNumber, n));
    }
    // TODO: write function here which goes through all the connections, and calls the right thing on the neuron.
}

NetworkInstance::NetworkInstance(const std::vector<Neuron> &neurons, const std::vector<Connection> &connections)
        : NetworkInstance(neurons, connections, DEFAULT_INPUTS, DEFAULT_OUTPUTS) {}

NetworkInstance::~NetworkInstance() {
}

Neuron *NetworkInstance::getNeuronWithInnovationNumber(int innovationNumber) {
    auto it = innovationToNeuronMap.find(innovationNumber);
    if (it == innovationToNeuronMap.end()) {
        std::cout << "warning: tried to get neuron with innovation number " << innovationNumber
                  << " returning nullptr since not found";
        return nullptr;
    }
    return &it->second;
}

Connection *NetworkInstance::getConnectionWithInnovationNumber(int innovationNumber) {
    auto it = innovationToConnectionMap.find(innovationNumber);
    if (it == innovationToConnectionMap.end()) {
        return nullptr;
    }
    return &it->second;
}

void NetworkInstance::recalculateConnections() {
    for (auto &it: innovationToNeuronMap) {
        it.second.incomingConnections.clear();
        it.second.outgoingConnections.clear();
    }

    for (auto &it: innovationToConnectionMap) {
        Connection &c = it.second;
        getNeuronWithInnovationNumber(c.to)->addConnection(&c);
        getNeuronWithInnovationNumber(c.from)->addConnection(&c);
    }
}

Neuron *NetworkInstance::getRandomNeuron() {
    if (innovationToNeuronMap.size() == 0) {
        return nullptr;
    }

    // Area for optimization: this function is very slow, instead we could keep track of neurons separately in a vector if needed
    const auto &it = std::next(std::begin(innovationToNeuronMap),
                               RandomGenerator::getRandomInRange(0, innovationToNeuronMap.size() - 1));
    return &it->second;
}

Connection *NetworkInstance::getRandomConnection() {
    if (innovationToConnectionMap.size() == 0) {
        return nullptr;
    }

    // Area for optimization: this function is very slow, instead we could keep track of connections separately in a vector if needed
    const auto &it = std::next(std::begin(innovationToConnectionMap),
                               RandomGenerator::getRandomInRange(0, innovationToConnectionMap.size() - 1));
    return &it->second;
}

void NetworkInstance::addNeuron(const Neuron n) {
    if (innovationToNeuronMap.count(n.innovationNumber) > 0) {
        throw std::runtime_error(
                "NetworkInstance::addNeuron: TRYING TO ADD NEURON TO NETWORK WHICH ALREADY EXISTS IN NETWORK!!");
    }
    innovationToNeuronMap.insert(std::pair<int, Neuron>(n.innovationNumber, n));
}

void NetworkInstance::addConnection(const Connection c) {
    if (innovationToConnectionMap.count(c.innovationNumber) > 0) {
        throw std::runtime_error(
                "NetworkInstance::addNeuron: TRYING TO ADD Connection TO NETWORK WHICH ALREADY EXISTS IN NETWORK!!");
    }

    innovationToConnectionMap.insert(std::pair<int, Connection>(c.innovationNumber, c));
}


void NetworkInstance::removeConnection(const Connection &c) {
    if (innovationToConnectionMap.count(c.innovationNumber) == 0) {
        throw std::runtime_error(
                "NetworkInstance::removeConnection: Trying to remove Connection in NETWORK WHICH DOES NOT EXIST IN NETWORK!!");
    }

    auto &outgoingVec = getNeuronWithInnovationNumber(c.from)->outgoingConnections;
    auto it1 = std::find(outgoingVec.begin(), outgoingVec.end(), c.innovationNumber);
    if (it1 != outgoingVec.end())
        outgoingVec.erase(it1);

    auto &incomingVec = getNeuronWithInnovationNumber(c.to)->incomingConnections;
    auto it2 = std::find(incomingVec.begin(), incomingVec.end(), c.innovationNumber);
    if (it2 != incomingVec.end())
        incomingVec.erase(it2);

    innovationToConnectionMap.erase(c.innovationNumber);
}


bool NetworkInstance::isInnovationNumberOfInputNeuron(int innovationNumber) {
    return std::find(inputs.begin(), inputs.end(), innovationNumber) != inputs.end();
}

bool NetworkInstance::isInnovationNumberOfOutputNeuron(int innovationNumber) {
    return std::find(outputs.begin(), outputs.end(), innovationNumber) != outputs.end();
}


void NetworkInstance::evaluateNetwork() {
    alreadyVisitedNeuronsWhenEvaluating.clear();

    for (int innovationNumber: outputs) {
        Neuron *n = getNeuronWithInnovationNumber(innovationNumber);
        if (!n) {
            throw std::runtime_error("OUTPUT NEURON NOT IN NETWORK!!");
        }

        n->calculateValue(*this);
    }
}
