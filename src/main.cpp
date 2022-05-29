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
void startGraphics()
{
    GraphicsManager::getInstance().startMainLoop();
    std::cout << "hello" << std::endl;
}

[[noreturn]] void NEATThread(){
    printf("Trying to start thread\n");


    // just for testing threading
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Neuron in1(0);
    Neuron in2(1);
    Neuron out1(2);

    Neuron h1(3);
    Neuron h2(100);
    Neuron h3(101);

    Connection con1(4, in1, h1, 1.0f, true);
    Connection con2(5, in2, h1, 1.0f, true);
    Connection con3(6, h1 ,out1, 2.0f, true);
    NetworkInstance n1({in1, in2, h1, out1}, {con1, con2, con3});

    con1.weight = 0.1f;
    con2.weight = 0.1f;
    con3.weight = 0.1f;
    Connection con4(7, in2, h2, 0.1f, true);
    Connection con5(8, h2, out1, 0.1f, true);
    NetworkInstance n2({in1, in2, h1,h2, out1}, {con1, con2, con3, con4, con5});

    n1.recalculateConnections();
    n2.recalculateConnections();



    GraphicsManager::getInstance().networkRenderer.currentNetwork = &n1;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    GraphicsManager::getInstance().networkRenderer.currentNetwork = &n2;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::unique_ptr<NetworkInstance> breed = NetworkBreeder::Crossover(n2, n1);



    while(true){
        GraphicsManager::getInstance().networkRenderer.currentNetworkMutex.lock();

        breed = NetworkBreeder::Crossover(n2, n1);
        GraphicsManager::getInstance().networkRenderer.currentNetwork = breed.get();

        GraphicsManager::getInstance().networkRenderer.currentNetworkMutex.unlock();


        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t1(NEATThread);

//    NEATThread();
    startGraphics();

    return 0;
}
