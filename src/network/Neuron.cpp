#include "Neuron.h"
#include <iostream>
#include "Connection.h"
#include <cmath>

Neuron::Neuron() : currentValue(0)
{
	std::cout << "made new neuron, innvation number is: " << this->innovationNumber << std::endl;
}

void Neuron::calculateValue()
{
	float sum = 0;
	for (auto it : this->incomingNeurons)
	{
		if (it->enabled)
		{
			sum += it->in->currentValue * it->weight;
		}
	}
	this->currentValue = activationFunction(sum);
}

float Neuron::activationFunction(float input)
{
	return input / (1 + abs(input));
}
