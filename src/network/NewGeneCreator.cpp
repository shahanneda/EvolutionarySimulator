//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "NewGeneCreator.h"
#include "Connection.h"

using namespace NeatSquared;


Connection NeatSquared::NewGeneCreator::getNewConnection(int from, int to) {

    Connection possibleNew(nextFreeInnovationNumber, from, to);

    //check if connection already exists with same from and too.
    auto it = connections.find(possibleNew);
    if (it == connections.end()) {
        // does not exist, so return a new one
        connections[possibleNew] = possibleNew.innovationNumber;
        nextFreeInnovationNumber++;
        return possibleNew;
    }

    // does exist already, so return that and don't increment the innovation number
    return it->first;
}


NewGeneCreator::NewGeneCreator()
        : nextFreeInnovationNumber(3) {}

Neuron NewGeneCreator::getNewNeuron() {
    return Neuron(nextFreeInnovationNumber++);
}
