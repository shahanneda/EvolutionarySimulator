//
// Created by Shahan Nedadahandeh on 2022-05-24.
//

#include "NetworkBreeder.h"
#include "NetworkInstance.h"
#include "utils/RandomGenerator.h"

using namespace NeatSquared;

const float NetworkBreeder::SAME_GENE_BOTH_PARENT_MORE_FIT_PROB = 0.5f;
using std::vector;
using std::vector;

std::unique_ptr<NetworkInstance> NetworkBreeder::Crossover(NetworkInstance &moreFitParent, NetworkInstance &lessFitParent) {
    /*
     * for gene in moreFitParent, if it is also in the lessFitParent, do 50/50 chance
     * if it is not in lessFitParent, just add it to the current geonome
     */

    vector<Neuron> newN;
    vector<Connection> newC;

    for(const auto &it : moreFitParent.innovationToNeuronMap){
        Neuron neuron = it.second;

        auto lessFitIt = lessFitParent.innovationToNeuronMap.find(neuron.innovationNumber);
        if(lessFitIt == lessFitParent.innovationToNeuronMap.end()){
            // found on more fit parent only, keep
            newN.push_back(neuron);
        }else{
            // found on both, so randomly select one
            if(RandomGenerator::getRandom() < SAME_GENE_BOTH_PARENT_MORE_FIT_PROB){
                newN.push_back(neuron);
            }else{
                newN.push_back(lessFitIt->second);
            }
        }
    }

    for(const auto &it : moreFitParent.innovationToConnectionMap){
        Connection connection = it.second;

        auto lessFitIt = lessFitParent.innovationToConnectionMap.find(connection.innovationNumber);
        if(lessFitIt == lessFitParent.innovationToConnectionMap.end()){
            // found on more fit parent only, keep
            newC.push_back(connection);
        }else{
            // found on both, so randomly select one
            if(RandomGenerator::getRandom() < SAME_GENE_BOTH_PARENT_MORE_FIT_PROB){
                newC.push_back(connection);
            }else{
                newC.push_back(lessFitIt->second);
            }
        }
    }

    auto network = std::unique_ptr<NetworkInstance >(new NetworkInstance(newN, newC));
    network->recalculateConnections();
    return network;
}


void NetworkBreeder::MutateNetwork(NetworkInstance &network) {
    
}
