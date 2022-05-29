//
// Created by Shahan Nedadahandeh on 2022-05-26.
//

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>


class RandomGenerator {
public:
    /*
     * Generates a random float between 0 and 1
     */
    static float getRandom();

    /*
     * Returns a random integer in a range, inclusive of both start and end.
     */
    static int getRandomInRange(int start, int end);

    /*
     * Returns a random float in a range, inclusive of both start and end
     */
    static float getRandomFloatInRange(float start, float end);

private:
    static std::uniform_int_distribution<std::mt19937::result_type> random1to100;
    static std::mt19937 rngGen;

};


#endif //RANDOMGENERATOR_H
