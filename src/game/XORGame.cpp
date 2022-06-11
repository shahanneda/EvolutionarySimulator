//
// Created by Shahan Nedadahandeh on 2022-05-30.
//

#include <thread>

#include "XORGame.h"
#include "utils/RandomGenerator.h"
#include <cmath>

using namespace NeatSquared;

XORGame::XORGame() : shouldSlowTraining(false) {
    this->numberOfInputs = 3;
    this->numberOfOutputs = 1;
}


float XORGame::evaluateNetwork(NetworkInstance &network) {
    Neuron *const input1 = network.getNeuronWithInnovationNumber(network.inputs[0]);
    Neuron *const input2 = network.getNeuronWithInnovationNumber(network.inputs[1]);
    Neuron *const input3 = network.getNeuronWithInnovationNumber(network.inputs[2]);
    Neuron *const out = network.getNeuronWithInnovationNumber(network.outputs[0]);

    if (!input1 || !input2 || !out) {
        throw std::runtime_error("XORGame: Evaluated with network that does not contain correct inputs/outputs!!");
    }


    // Start off with some initial fitness so that evolution will get a start (else everything would be eliminated right at the start)
    float fitness = 0;

    // TODO: Add options to slow down training here so it can better be seen in the UI

//    float casesCorrect = 0;
    for (int i = 0; i < 4; i++) {
        int in1 = RandomGenerator::getRandomFloatInRange(0, 1) > 0.5;
        int in2 = RandomGenerator::getRandomFloatInRange(0, 1) > 0.5;
        if (i == 0) {
            in1 = 0;
            in2 = 0;
        } else if (i == 1) {
            in1 = 1;
            in2 = 0;
        } else if (i == 2) {
            in1 = 0;
            in2 = 1;
        } else if (i == 3) {
            in1 = 1;
            in2 = 1;
        }


        int expectedOutput = in1 != in2;
        input1->currentValue = (float) in1;
        input2->currentValue = (float) in2;
        input3->currentValue = 1;
        network.evaluateNetwork();

        float actualOutput = out->currentValue;
//        printf("inputs were: %.2f and %.2f output is %.2f\n", input1->currentValue, input2->currentValue, actualOutput);

        fitness += differenceSquaredFitness(actualOutput, expectedOutput);
    }
    return fitness * fitness;
}

float XORGame::differenceSquaredFitness(float actual, float expected) {
    float fitness = 1 - abs(expected - actual);
    printf(" actual is %.2f expected is %.2f giving fitness %.2f\n", actual, expected, fitness);
    return fitness;
}

float XORGame::logisticFitness(float actual, int expected) {
    return -((1 - expected) * log(actual) + (expected) * log(1 - actual));
}
