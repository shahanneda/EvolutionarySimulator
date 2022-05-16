#ifndef __NETWORK__
#define __NETWORK__

#include "Neuron.h"
#include "Connection.h"
#include <vector>
#include <unordered_map>

class Network
{
public:
	Network(std::unordered_map<int, Connection> *connections, std::unordered_map<int, Neuron> *neurons);
	~Network();

	std::vector<Neuron *> inputs;
	std::vector<Neuron *> outputs;

	std::unordered_map<int, Connection> innovationToConnectionMap;
	std::unordered_map<int, Neuron> innovationToNeuronMap;
};

#endif