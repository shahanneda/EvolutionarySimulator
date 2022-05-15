#include "Gene.h"
class Connection : public Gene
{
public:
	/*
		Innovation number of input neuron
	*/
	int in;
	/*
		Innovation number of output neuron
	*/
	int out;

	float weight;
	bool enabled;
};