#include "Neuron.h"
#include <iostream>
#include "Connection.h"
#include <cmath>


using namespace NeatSquared;
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

void Neuron::removeConnection(Connection* con) {
    if(this->innovationNumber == con->from){
        auto i = std::find(incomingConnections.begin(), incomingConnections.end(), con->innovationNumber);
        if (i != incomingConnections.end())
            incomingConnections.erase(i);
    }else if (this->innovationNumber == con->to){
        auto i = std::find(outgoingConnections.begin(), outgoingConnections.end(), con->innovationNumber);
        if (i != outgoingConnections.end())
            outgoingConnections.erase(i);
    }else{
        throw std::runtime_error("Trying to remove connection from neuron which does not include neuron! ");
    }
}

void Neuron::addConnection(Connection* con) {
    if(this->innovationNumber == con->from){
        this->outgoingConnections.push_back(con->innovationNumber);
    }else if (this->innovationNumber == con->to){
        this->incomingConnections.push_back(con->innovationNumber);
    }else{
        throw std::runtime_error("Trying to add connection to neuron which does not include neuron! ");
    }
}
