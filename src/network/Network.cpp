#include <algorithm>
#include "Network.h"

using namespace NeatSquared;

Network::Network(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                 const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs)
        : innovationToConnectionMap(
        innovationToConnectionMap), innovationToNeuronMap(innovationToNeuronMap), inputs(inputs) {}

Network::~Network() {
}