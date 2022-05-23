#ifndef __NETWORK__
#define __NETWORK__

#include "Neuron.h"
#include "Connection.h"
#include <vector>
#include <unordered_map>

class Network
{
public:
    Network(const std::unordered_map<int, Connection> &innovationToConnectionMap,
            const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs);

    ~Network();

	std::unordered_map<int, Connection> innovationToConnectionMap;
	std::unordered_map<int, Neuron> innovationToNeuronMap;

    /*
     * Innovation number of all neurons which are inputs
     */
    std::vector<int> inputs;
};

#endif