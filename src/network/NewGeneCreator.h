//
// Created by Shahan Nedadahandeh on 2022-05-23.
//
#include <algorithm>
#include <unordered_map>

#include "Connection.h"
#include "Neuron.h"

#ifndef INNOVATIONNUMBERMANAGER_H
#define INNOVATIONNUMBERMANAGER_H



namespace NeatSquared{
    class NewGeneCreator {
    public:
        NewGeneCreator();

        /*
         * Gets a new connection from a neuron with from's innovation number to a neuron with to's innovation number
         */
        Connection getNewConnection(int from, int to);

        /*
         * Gets a new node.
         */
        Neuron getNewNeuron();

    private:
        int nextFreeInnovationNumber;
        std::unordered_map<Connection, int, ConnectionHasher, ConnectionEqual> connections;
    };
}
#endif //INNOVATIONNUMBERMANAGER_H
