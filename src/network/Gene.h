
#ifndef __GENE__

#define __GENE__

class Gene
{
public:
	Gene();
	const int innovationNumber;

private:
	static int nextFreeInnovationNumber;
};

#endif