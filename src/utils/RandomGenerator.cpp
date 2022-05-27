//
// Created by Shahan Nedadahandeh on 2022-05-26.
//

#include "utils/RandomGenerator.h"

float RandomGenerator::getRandom() {
    return ((float)random1to100(rngGen)/100.0f);
}


void RandomGenerator::init() {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);

    RandomGenerator::rngGen = rng;
    RandomGenerator::random1to100 = dist;
}
