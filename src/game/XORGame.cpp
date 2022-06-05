//
// Created by Shahan Nedadahandeh on 2022-05-30.
//

#include <thread>

#include "XORGame.h"
#include "utils/RandomGenerator.h"
#include <cmath>

using namespace NeatSquared;

XORGame::XORGame() {
    this->numberOfInputs = 2;
    this->numberOfOutputs = 1;
}


float XORGame::evaluateNetwork(NetworkInstance &network) {
    Neuron *const input1 = network.getNeuronWithInnovationNumber(network.inputs[0]);
    Neuron *const input2 = network.getNeuronWithInnovationNumber(network.inputs[1]);
    Neuron *const out = network.getNeuronWithInnovationNumber(network.outputs[0]);

    if (!input1 || !input2 || !out) {
        throw std::runtime_error("XORGame: Evaluated with network that does not contain correct inputs/outputs!!");
    }


    // Start off with some initial fitness so that evolution will get a start (else everything would be eliminated right at the start)
    float fitness = 1;

    // TODO: Add options to slow down training here so it can better be seen in the UI

    for (int i = 0; i < numberOfIterations; i++) {
        int in1 = RandomGenerator::getRandomFloatInRange(0, 1) > 0.5;
        int in2 = RandomGenerator::getRandomFloatInRange(0, 1) > 0.5;
        int expectedOutput = in1 != in2;

        input1->currentValue = (float) in1;
        input2->currentValue = (float) in2;
        network.evaluateNetwork();

        float actualOutput = out->currentValue;

        if (actualOutput <= 0) {
            continue;
        }

        fitness += logisticFitness(actualOutput, expectedOutput);
    }
    return fitness;
}


float XORGame::logisticFitness(float actual, int expected) {
    return -((1 - expected) * log(actual) + (expected) * log(1 - actual));
}
