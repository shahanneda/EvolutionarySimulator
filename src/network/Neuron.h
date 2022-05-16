#include "Gene.h"
#include "Connection.h"
#include <vector>

class Neuron : public Gene
{
public:
	Neuron();

	/*
		Calculates the neurans current value from all of its incoming connections
	*/
	void calculateValue();

	/*
		The current value of this neuron. Used when running the network;
	*/
	float currentValue;

	/*
		All connections that lead into this neuron;
	*/
	std::vector<Connection *> incomingNeurons;

	/*
		The activation function of this node. Currently implemented as sigmoid.
	*/
	static float activationFunction(float value);
};
