//
// Created by Shahan Nedadahandeh on 2022-05-23.
//
#include <algorithm>
#include <unordered_map>

#include "Connection.h"
#include "Neuron.h"

#ifndef INNOVATIONNUMBERMANAGER_H
#define INNOVATIONNUMBERMANAGER_H


namespace NeatSquared {
    /*
     *  NewGeneCreator is responsible for creating new neurons and connections, assigning the correct innovation number to the new neurons/connections depending on whether that gene had been seen before in history or not.
     */
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
