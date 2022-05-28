

#include "Gene.h"
#include "network/Neuron.h"

#ifndef __CONNECTION__
#define __CONNECTION__

namespace NeatSquared {
    class Connection : public Gene {
    public:
        Connection(int innovationNumber, int from, int to, float weight, bool enabled);
        Connection(int innovationNumber, Neuron &from, Neuron &to, float weight, bool enabled);

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
