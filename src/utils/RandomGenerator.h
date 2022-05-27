//
// Created by Shahan Nedadahandeh on 2022-05-26.
//

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>


class RandomGenerator {
public:
    static void init();
    static float getRandom();
private:
    static std::uniform_int_distribution<std::mt19937::result_type> random1to100;
    static std::mt19937 rngGen;
};


#endif //RANDOMGENERATOR_H
