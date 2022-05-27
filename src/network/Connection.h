#ifndef __CONNECTION__
#define __CONNECTION__


#include "Neuron.h"
#include "Gene.h"

namespace NeatSquared {
    class Neuron;

    class Connection : public Gene {
    public:
        Connection(int innovationNumber, int from, int to, float weight, bool enabled);

        /*
         * Innovation number of input neuron, where this connection starts
        */
        int from;

        /*
            Innovation number of output neuron, where this connection ends
        */
        int to;

        float weight;
        bool enabled;
    };
}
#endif
