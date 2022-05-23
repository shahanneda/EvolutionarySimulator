#ifndef __CONNECTION__
#define __CONNECTION__


#include "Neuron.h"
#include "Gene.h"

namespace NeatSquared {
    class Neuron;

    class Connection : public Gene {
    public:
        Connection(int innovationNumber, int in, int out, float weight, bool enabled);

        /*
         * Innovation number of input neuron
        */
        int in;

        /*
            Innovation number of output neuron
        */
        int out;

        float weight;
        bool enabled;
    };
}
#endif
