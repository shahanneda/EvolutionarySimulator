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

        NetworkInstance(const std::vector<Neuron> &neurons, const std::vector<Connection> &connections,
                        std::vector<int> inputs, std::vector<int> outputs);

        NetworkInstance(const std::vector<Neuron> &neurons, const std::vector<Connection> &connections);

        ~NetworkInstance();


        /*
         * Resets and recalculates the incomingConnections and outgoingConnections fields on all it's neurons
         */
        void recalculateConnections();

        /*
         * Add a connection to this network; WARNING: need to call recalculate connections before rendering after calling this function!!
         */
        void addConnection(Connection c);

        /*
         * Add a neuron to this network; WARNING: need to call recalculate connections before rendering after calling this function!!
         */
        void addNeuron(Neuron n);

        /*
         *  Get a neuron in this NetworkInstance with its innovation number;
         */
        Neuron *getNeuronWithInnovationNumber(int i);


        /*
         * Gets a random neuron in this network
         */
        Neuron &getRandomNeuron();

        /*
         * Get a connection in this NetworkInstance with its innovation number
         */
        Connection *getConnectionWithInnovationNumber(int i);


        /*
         * Gets a random connection in this network
         */
        Connection &getRandomConnection();


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


        static std::vector<int> DEFAULT_INPUTS;
        static std::vector<int> DEFAULT_OUTPUTS;
    };

}

#endif //NetworkInstanceINSTANCE_H
