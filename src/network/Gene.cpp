#include "Gene.h"


#include <functional>


using namespace NeatSquared;
Gene::Gene(int innovationNumber) : innovationNumber(innovationNumber)
{
}

bool Gene::operator==(const Gene &rhs) const {
    return innovationNumber == rhs.innovationNumber;
}

bool Gene::operator!=(const Gene &rhs) const {
    return !(rhs == *this);
}

Gene::Gene(const Gene &g): innovationNumber(g.innovationNumber) {
}

