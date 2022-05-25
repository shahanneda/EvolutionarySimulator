#include <algorithm>
#include "network/NetworkInstance.h"

using namespace NeatSquared;

NetworkInstance::NetworkInstance(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                 const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs, std::vector<int> outputs)
        : innovationToConnectionMap(
        innovationToConnectionMap), innovationToNeuronMap(innovationToNeuronMap), inputs(inputs), outputs(outputs) {}

NetworkInstance::~NetworkInstance() {
}

Neuron *NetworkInstance::getNeuronWithInnovationNumber(int innovationNumber) {
    auto it = innovationToNeuronMap.find(innovationNumber);
    if (it == innovationToNeuronMap.end()) {
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
