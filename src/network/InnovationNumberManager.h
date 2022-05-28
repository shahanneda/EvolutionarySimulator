//
// Created by Shahan Nedadahandeh on 2022-05-23.
//
#include "network/Connection.h"
#include <algorithm>

#ifndef INNOVATIONNUMBERMANAGER_H
#define INNOVATIONNUMBERMANAGER_H



namespace NeatSquared{
    class InnovationNumberManager {

        /*
         * Gets a new connection from a neuron with from's innovation number to a neuron with to's innovation number
         */
        std::unique_ptr<Connection> getNewConnection(int from, int to);
    };
}
#endif //INNOVATIONNUMBERMANAGER_H
