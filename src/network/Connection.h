#ifndef __CONNECTION__
#define __CONNECTION__


#include "Neuron.h"
#include "Gene.h"
class Neuron;

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
#endif
