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
    GraphicsManager::getInstance().startMainLoop();
}

[[noreturn]] void NEATThread() {
    XORGame xorGame;
    BreedingManager manager(xorGame);

    while (true) {

    }
}

int main() {

    std::thread t1(NEATThread);
    startGraphics();

    return 0;
}
