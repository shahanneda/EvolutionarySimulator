#include "Neuron.h"
#include <iostream>
#include "Connection.h"
#include <cmath>


void Neuron::calculateValue()
{
//	float sum = 0;
//	for (auto it : this->incomingNeurons)
//	{
//		if (it->enabled)
//		{
//			sum += it->in->currentValue * it->weight;
//		}
//	}
//	this->currentValue = activationFunction(sum);
}

float Neuron::activationFunction(float input)
{
	return input / (1 + abs(input));
}

Neuron::Neuron(int innovationNumber) : Gene(innovationNumber) {}
