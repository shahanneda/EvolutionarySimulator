#include <algorithm>
#include "Network.h"

using namespace NeatSquared;

Network::Network(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                 const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs, std::vector<int> outputs)
        : innovationToConnectionMap(
        innovationToConnectionMap), innovationToNeuronMap(innovationToNeuronMap), inputs(inputs), outputs(outputs) {}

Network::~Network() {
}

Neuron *Network::getNeuronWithInnovationNumber(int innovationNumber) {
    auto it = innovationToNeuronMap.find(innovationNumber);
    if (it == innovationToNeuronMap.end()) {
        return nullptr;
    }
    return &it->second;
}

Connection *Network::getConnectionWithInnovationNumber(int innovationNumber) {
    auto it = innovationToConnectionMap.find(innovationNumber);
    if (it == innovationToConnectionMap.end()) {
        return nullptr;
    }
    return &it->second;
}
