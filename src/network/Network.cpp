#include <algorithm>

Network::Network(std::unordered_map<int, Connection> *connections, std::unordered_map<int, Neuron> *neurons)
{
	std::copy(connections->begin, connections->end, this->innovationConnectionsMap->begin());
	std::copy(neurons->begin, neurons->end, this->innovationNeuronMap->begin());
}

Network::~Network()
{
}