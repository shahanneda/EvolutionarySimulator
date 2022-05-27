#include <algorithm>
#include "network/NetworkInstance.h"

using namespace NeatSquared;

using std::pair;
std::vector<int> NetworkInstance::DEFAULT_INPUTS = {0, 1};
std::vector<int> NetworkInstance::DEFAULT_OUTPUTS = {2};


NetworkInstance::NetworkInstance(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                 const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs, std::vector<int> outputs)
        : innovationToConnectionMap(
        innovationToConnectionMap), innovationToNeuronMap(innovationToNeuronMap), inputs(inputs), outputs(outputs) {}

NetworkInstance::NetworkInstance( const std::vector<Neuron> &neurons, const std::vector<Connection>&connections, std::vector<int> inputs, std::vector<int> outputs): inputs(inputs), outputs(outputs){
    for(auto c : connections){
        innovationToConnectionMap.insert(pair<int, Connection>(c.innovationNumber, c));
    }
    for(auto n : neurons){
        innovationToNeuronMap.insert(pair<int, Neuron>(n.innovationNumber, n));
    }
}

NetworkInstance::NetworkInstance( const std::vector<Neuron> &neurons, const std::vector<Connection>&connections) : NetworkInstance(neurons, connections, DEFAULT_INPUTS, DEFAULT_OUTPUTS){}

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

