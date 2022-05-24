#ifndef __NETWORK__
#define __NETWORK__

#include "Neuron.h"
#include "Connection.h"
#include <vector>
#include <unordered_map>

namespace NeatSquared {
    class Network {
    public:
        Network(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs, std::vector<int> outputs);

        ~Network();

        std::unordered_map<int, Connection> innovationToConnectionMap;
        std::unordered_map<int, Neuron> innovationToNeuronMap;

        /*
         * Innovation number of all neurons which are inputs
         */
        std::vector<int> inputs;

        /*
         * Innovation number of all neurons which are outputs
         */
        std::vector<int> outputs;


        /*
         *  Get a neuron in this network with its innovation number;
         */
        Neuron * getNeuronWithInnovationNumber(int i);

        /*
         * Get a connection in this network with its innovation number
         */
        Connection * getConnectionWithInnovationNumber(int i);
    };

}
#endif