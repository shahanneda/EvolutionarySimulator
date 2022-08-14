//
// Created by Shahan Nedadahandeh on 2022-05-26.
//

#include "utils/RandomGenerator.h"

float RandomGenerator::getRandom() {
    return ((float) random1to100(rngGen) / 100.0f);
}


std::random_device dev;

/*
 * Because the NEAT algorithm has a great deal of randomness, the amount of training time can vary between 10 - 200 generations, depending on the random seed.
 * I've selected some random seeds which are on the lower side of the training time, so that demos are faster,
 * (especially important for people viewing the browser with webassembly, since waiting 200 generations is hard
 * */

// Good seeds for 10 by 10
// 0, 1

// Good seeds for 15x15
// seed format: seed (first above 300 fitness/above 1500)
// 1 (6 / 30), 2 (18 / 30) , 10 (gen 15/24), 11 (6 / 14), 13 (9/30), 15, 16, 21, 22, 24, 29


// Use c-style rand() for seed selection since I don't want to effect the c++ randomness

const int seeds[] = {1, 2, 13, 15, 22, 29};
int seedCount = sizeof(seeds) / sizeof(int);

std::mt19937 RandomGenerator::rngGen(seeds[rand() % seedCount]);

std::uniform_int_distribution<std::mt19937::result_type> RandomGenerator::random1to100(1, 100);

int RandomGenerator::getRandomInRange(int start, int end) {
    // add 0.5 since casting to int rounds down
    float num = getRandom() * ((float) end - (float) start) + 0.5f;
    return ((int) num + start);
}

float RandomGenerator::getRandomFloatInRange(float start, float end) {
    float num = getRandom() * (end - start);
    return (num + start);
}

