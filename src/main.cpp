#include <unordered_map>
#include <thread>
#include <iostream>
#include <mutex>

#include "network/Connection.h"
#include "network/Neuron.h"
#include "network/NetworkInstance.h"
#include "network/NetworkBreeder.h"
#include "utils/RandomGenerator.h"
#include "game/XORGame.h"
#include "graphics/GraphicsManager.h"
#include "evolution/BreedingManager.h"

using namespace NeatSquared;

void startGraphics() {
    printf("starting graphics\n");
    GraphicsManager::getInstance().startMainLoop();
}

[[noreturn]] void NEATThread() {
    XORGame xorGame;
    BreedingManager manager(xorGame);

    GraphicsManager::getInstance().breedingManager = &manager;


    for (int i = 0; i < 100; i++) {
        manager.evaluateFitnessOfGeneration(manager.getCurrentGeneration());
        manager.breedNextGeneration();
    }

    printf(" Finished NEAT Thread init\n");
    while (true) {
//        if (GraphicsManager::getInstance().networkRenderer.currentNetwork) {
//            GraphicsManager::getInstance().networkRenderer.currentNetwork->evaluateNetwork();
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    GraphicsManager::getInstance();
    std::thread t1(NEATThread);
    startGraphics();


    return 0;
}
