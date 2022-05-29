//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "InnovationNumberManager.h"
#include "Connection.h"

using namespace NeatSquared;


Connection NeatSquared::InnovationNumberManager::getNewConnection(int from, int to) {
    Connection possibleNew(nextFreeInnovationNumber, from, to);

    //check if connection already exists with same from and too.
    auto it = connections.find(possibleNew);
    if(it == connections.end()){
        // does not exist, so return a new one
        connections[possibleNew] = possibleNew.innovationNumber;
        nextFreeInnovationNumber++;
        return possibleNew;
    }

    // does not exist, so return that and dont increment the innovation number
    return it->first;
}



InnovationNumberManager::InnovationNumberManager()
        : nextFreeInnovationNumber(0){}

Neuron InnovationNumberManager::getNewNeuron() {
    return Neuron(nextFreeInnovationNumber++);
}
