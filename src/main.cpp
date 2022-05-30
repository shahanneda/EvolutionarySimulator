#include <unordered_map>
#include <thread>
#include <iostream>
#include <mutex>

#include "network/Connection.h"
#include "network/Neuron.h"
#include "graphics/GraphicsManager.h"
#include "network/NetworkInstance.h"
#include "utils/RandomGenerator.h"
#include "network/NetworkBreeder.h"

using namespace NeatSquared;

void startGraphics() {
    GraphicsManager::getInstance().startMainLoop();
}

[[noreturn]] void NEATThread() {
    printf("Trying to start thread\n");


    NetworkBreeder breeder;
    // just for testing threading
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Neuron in1(0);
    Neuron in2(1);
    Neuron out1(2);

//    Neuron h1(3);
//    Neuron h2(100);
//    Neuron h3(101);
////
//    Connection con1(4, in1, in2, 1.0f, true);
//    Connection con2(5, in1, out1, 1.0f, true);
//    Connection con3(6, out1, in2, 2.0f, true);

//    Connection c1(3, 0, 1, 1.0f, true);
//    Connection c2(4, 2, 0, 1.0f, true);

    NetworkInstance n1({in1, in2, out1}, {});



//    con1.weight = 0.1f;
//    con2.weight = 0.1f;
//    con3.weight = 0.1f;
//    Connection con4(7, in2, h2, 0.1f, true);
//    Connection con5(8, h2, out1, 0.1f, true);
//    NetworkInstance n2({in1, in2, h1, h2, out1}, {});

//    n2.recalculateConnections();
    n1.recalculateConnections();


//    GraphicsManager::getInstance().networkRenderer.currentNetwork = &n1;
//    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    GraphicsManager::getInstance().networkRenderer.currentNetwork = &n1;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::unique_ptr<NetworkInstance> breed = breeder.crossover(n1, n1);
    GraphicsManager::getInstance().networkRenderer.currentNetwork = breed.get();


    while (true) {
        GraphicsManager::getInstance().networkRenderer.currentNetworkMutex.lock();
        breed = breeder.crossover(*breed.get(), *breed.get());
        GraphicsManager::getInstance().networkRenderer.currentNetwork = breed.get();
        GraphicsManager::getInstance().networkRenderer.currentNetworkMutex.unlock();
        breed->evaluateNetwork();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t1(NEATThread);

//    NEATThread();
    startGraphics();

    return 0;
}
