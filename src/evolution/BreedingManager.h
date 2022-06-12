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
        static const float SPECIES_BREEDING_PERCENT;


    public:
        BreedingManager(Game &game);

        Game &game;

        std::vector<Generation> generations;

        int getCurrentGenerationNumber();

        /*
         * Evaluate the fitness of a generation
         */
        void evaluateFitnessOfGeneration(Generation &generation);

        /*
         * Get the current generation
         */
        Generation &getCurrentGeneration();

        /*
         * Creates the next generation by breeding from this generation. Assumes that evaluateFitnessOfGeneration has already been called for the current generation.
         */
        void breedNextGeneration();


    private:
        void createStartingGeneration();

        NewGeneCreator geneCreator;
        NetworkBreeder networkBreeder;

        void evaluateFitnessOfSpecies(Species &species);


    };


}


#endif //BREEDINGMANAGER_H
