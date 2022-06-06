//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#ifndef NetworkInstanceINSTANCE_H
#define NetworkInstanceINSTANCE_H


#include "Neuron.h"
#include "Connection.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace NeatSquared {
    class NetworkInstance {
    public:

        /*
         * Make a new Network from the given neurons and connections. inputs/outputs vector should contain the innovationNumber of the neurons which are inputs and outputs respectively
         */
        NetworkInstance(const std::vector<Neuron> &neurons, const std::vector<Connection> &connections,
                        std::vector<int> inputs, std::vector<int> outputs);

        /*
         * Make a network using the NetworkInstance::DEFAULT_INPUTS and NetworkInstance::DEFAULT_OUTPUTS. Use only for quick testing when manually creating networks.
         */
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
        Neuron *getRandomNeuron();

        /*
         * Get a connection in this NetworkInstance with its innovation number
         */
        Connection *getConnectionWithInnovationNumber(int i);


        /*
         * Gets a random connection in this network
         */
        Connection *getRandomConnection();


        /*
         * Remove a connection from this network; WARNING: need to call recalculate connections before rendering after calling this function!!
         */
        void removeConnection(const Connection &c);

        /*
         * Checks if an innovation number is off an input neuron
         */
        bool isInnovationNumberOfInputNeuron(int innovationNumber);

        /*
         * Checks if an innovation number is off an output neuron
         */
        bool isInnovationNumberOfOutputNeuron(int innovationNumber);

        /*
         * Evaluates a network (i.e. takes values from the input neurons and passes that through the network all the way to the output neurons)
         */
        void evaluateNetwork();

        /*
         * Gets how closely matched this network is with another network.
         * */
        float getCompatibilityDistanceWith(NetworkInstance &network);

        /*
         * Evaluates if the networks compatibility distance is close enough to allow the two networks to be in the same species.
         */
        bool isCompatibleWith(NetworkInstance &network);

        /*
         * Make a clone of this network
         */
        std::unique_ptr<NetworkInstance> clone();

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

        /*
         * Utility used when evaluating network by neurons to keep track of loops
         */
        std::unordered_set<int> alreadyVisitedNeuronInnovationNumbersWhenEvaluating;

        /*
         * Identification number of this network in its generation, -1 if this network has not been assigned to a generation yet
         */
        int id;

        /*
         * The fitness that this network showed the last time it was evaluated.
         */
        float lastEvaluationFitness;

    private:
        NetworkInstance(const std::unordered_map<int, Connection> &innovationToConnectionMap,
                        const std::unordered_map<int, Neuron> &innovationToNeuronMap, std::vector<int> inputs,
                        std::vector<int> outputs);
    };

}

#endif //NetworkInstanceINSTANCE_H
