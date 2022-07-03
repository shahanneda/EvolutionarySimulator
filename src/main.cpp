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
    SnakeGame snakeGame;
    BreedingManager manager(snakeGame);
    GraphicsManager &graphicsManager = GraphicsManager::getInstance();

    graphicsManager.breedingManager = &manager;
    graphicsManager.snakeRenderer.game = &snakeGame;


    for (int i = 0; i < 1000; i++) {
        manager.evaluateFitnessOfGeneration(manager.getCurrentGeneration());
        manager.breedNextGeneration();
    }

    printf(" Finished NEAT Thread init\n");
    while (true) {
        if (graphicsManager.snakeRenderer.game &&
            graphicsManager.networkRenderer.currentNetwork) {
            graphicsManager.snakeRenderer.game->evaluateNetwork(*graphicsManager.networkRenderer.currentNetwork);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        snakeGame.nextGameIteration();
//        if (GraphicsManager::getInstance().networkRenderer.currentNetwork) {
//            GraphicsManager::getInstance().networkRenderer.currentNetwork->evaluateNetwork();
//        }
    }
}

int main() {
    GraphicsManager::getInstance();
    std::thread t1(NEATThread);
    startGraphics();


    return 0;
}
