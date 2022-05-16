#include "Neuron.h"
#include <iostream>
#include "Connection.h"

Neuron::Neuron() : currentValue(0)
{
	std::cout << "made new neuron, innvation number is: " << this->innovationNumber << std::endl;
}

void Neuron::calculateValue()
{
	float sum = 0;
	for (auto it : this.incomingNeurons)
	{
	}
}
