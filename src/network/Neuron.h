#include "Gene.h"

#include <vector>


#ifndef __NEURON__
#define __NEURON__


namespace NeatSquared {

    class NetworkInstance;

    class Connection;

    class Neuron : public Gene {
    public:
        Neuron(int innovationNumber);


        /*
         * Innovation number of all outgoing connections
         */
        std::vector<int> outgoingConnections;

        /*
         * Innovation number of all incoming connections.
         */
        std::vector<int> incomingConnections;


        void addConnection(Connection *connection);

        void removeConnection(Connection *connection);

        /*
            Calculates the neurons currentValue from all of its incoming connections.
        */
        void calculateValue(NetworkInstance &network);

        /*
            The current value of this neuron. Used when running the network;
        */
        float currentValue;

        /*
            All connections that lead into this neuron;
        */
        std::vector<Connection *> incomingNeurons;

        /*
            The activation function of this node. Currently implemented as sigmoid.
        */
        static float activationFunction(float value);
    };
}

#endif
