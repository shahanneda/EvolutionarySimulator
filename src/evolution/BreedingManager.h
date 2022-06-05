//
// Created by Shahan Nedadahandeh on 2022-05-31.
//

#ifndef BREEDINGMANAGER_H
#define BREEDINGMANAGER_H


#include <vector>
#include <unordered_map>
#include "game/Game.h"


#include "evolution/Generation.h"
#include "evolution/Species.h"
#include "network/NewGeneCreator.h"
#include "network/NetworkBreeder.h"

namespace NeatSquared {
    class BreedingManager {
    public:
        static const float NETWORK_COMPATIBILITY_MATCHING_GENE_CONSTANT;
        static const float NETWORK_COMPATIBILITY_WEIGHT_DIFFERENCE_CONSTANT;
        static const float SAME_SPECIES_NETWORK_COMPATIBILITY_CUTOFF;
        static const int MAX_NETWORKS_IN_GENERATION;


    public:
        BreedingManager(Game &game);

        Game &game;

        std::vector<Generation> generations;

        int currentGeneration = 0;

    private:
        void createStartingGeneration();

        NewGeneCreator geneCreator;
        NetworkBreeder networkBreeder;

    };


}


#endif //BREEDINGMANAGER_H
