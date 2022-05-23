
#ifndef __GENE__

#define __GENE__

/*
Base class of network that stores the innovation number.
*/
class Gene
{
public:
	Gene();
	/*
		A unique number assigned to a gene at the time of creation which tracks the historical origin of a gene and allows genomes to be compared with each other.
	*/
	const int innovationNumber;

private:
	static int nextFreeInnovationNumber;
};

#endif