#include "Gene.h"

int Gene::nextFreeInnovationNumber = 0;

Gene::Gene() : innovationNumber(nextFreeInnovationNumber)
{
	nextFreeInnovationNumber += 1;
}