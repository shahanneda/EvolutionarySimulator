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


    manager.evaluateFitnessOfGeneration(manager.getCurrentGeneration());
    manager.breedNextGeneration();
    graphicsManager.snakeRenderer.game = &snakeGame;
    for (int i = 0; i < 5000; i++) {
        manager.evaluateFitnessOfGeneration(manager.getCurrentGeneration());
        manager.breedNextGeneration();

        // pause training if requested
        while (manager.shouldPauseTraining) {
            if (graphicsManager.snakeRenderer.game &&
                graphicsManager.networkRenderer.currentNetwork) {
                {
                    if (!manager.hasAutoSetSlowGameThisPause) {
                        manager.hasAutoSetSlowGameThisPause = true;
                        snakeGame.shouldSlowGame = true;
                    }

                    if (graphicsManager.networkPicker.selectedNetwork) {
                        std::lock_guard<std::mutex> networkLock(graphicsManager.networkRenderer.currentNetworkMutex);
                        graphicsManager.networkRenderer.currentNetwork = graphicsManager.networkPicker.selectedNetwork;
                    }

                    graphicsManager.snakeRenderer.game->evaluateNetwork(
                            *graphicsManager.networkRenderer.currentNetwork);
                }
            }
        };


        // If game is unpaused, reset boolean
        manager.hasAutoSetSlowGameThisPause = false;
    }

    printf(" Finished NEAT Thread init\n");
    while (true) {
        if (graphicsManager.snakeRenderer.game &&
            graphicsManager.networkRenderer.currentNetwork) {
            graphicsManager.snakeRenderer.game->evaluateNetwork(*graphicsManager.networkRenderer.currentNetwork);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }
}

int main() {
    GraphicsManager::getInstance();
    std::thread t1(NEATThread);
    startGraphics();


    return 0;
}
