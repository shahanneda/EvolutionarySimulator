//
// Created by Shahan Nedadahandeh on 2022-05-26.
//

#include "utils/RandomGenerator.h"

float RandomGenerator::getRandom() {
    return ((float)random1to100(rngGen)/100.0f);
}


std::random_device dev;
std::mt19937 RandomGenerator::rngGen(dev());
std::uniform_int_distribution<std::mt19937::result_type> RandomGenerator::random1to100(1,100);

int RandomGenerator::getRandomInRange(int start, int end) {
    // add 0.5 since casting to int rounds down
    float num = getRandom()*((float)end-(float)start) + 0.5f;
    return((int)num + start);
}

