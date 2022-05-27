//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#include "NetworkBreeder.h"
#include "NetworkInstance.h"

using namespace NeatSquared;

std::unique_ptr<NetworkInstance> NetworkBreeder::Crossover(NetworkInstance *moreFitParent, NetworkInstance *lessFitParent) {
    /*
     * for gene in moreFitParent, if it is also in the lessFitParent, do 50/50 chance
     * if it is not in lessFitParent, just add it to the current geonome
     */



    return std::unique_ptr<NetworkInstance >();
}
