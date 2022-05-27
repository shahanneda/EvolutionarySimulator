//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#ifndef NetworkInstanceINSTANCE_H
#define NetworkInstanceINSTANCE_H


#include "Neuron.h"
#include "Connection.h"
#include <vector>
#include <unordered_map>

namespace NeatSquared {
    class NetworkInstance {
    public:
        NetworkInstance(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs,
                std::vector<int> outputs);

        NetworkInstance( const std::vector<Neuron> &neurons, const std::vector<Connection>&connections, std::vector<int> inputs, std::vector<int> outputs);
        NetworkInstance( const std::vector<Neuron> &neurons, const std::vector<Connection>&connections);

        ~NetworkInstance();

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
         *  Get a neuron in this NetworkInstance with its innovation number;
         */
        Neuron* getNeuronWithInnovationNumber(int i);

        /*
         * Get a connection in this NetworkInstance with its innovation number
         */
        Connection *getConnectionWithInnovationNumber(int i);

        static std::vector<int> DEFAULT_INPUTS;
        static std::vector<int> DEFAULT_OUTPUTS;

    };

}

#endif //NetworkInstanceINSTANCE_H
