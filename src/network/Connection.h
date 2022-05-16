#include "Gene.h"
#include "Neuron.h"

class Connection : public Gene
{
public:
	/*
		Input neuron
	*/
	Neuron *in;
	/*
		Output neuron
	*/
	Neuron *out;

	float weight;

	bool enabled;
};