#include <unordered_map>
#include <thread>
#include <iostream>
#include "graphics/GraphicsManager.h"
#include "network/Neuron.h"
#include "network/Network.h"

using namespace NeatSquared;
void startGraphics()
{
    GraphicsManager::getInstance().startMainLoop();
    std::cout << "hello" << std::endl;
}

void NEATThread(){
    printf("Trying to start thread\n");
    // just for testing threading
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Neuron in1(0);
    Neuron in2(1);

    Neuron out1(2);


    Connection con1(3, in1.innovationNumber, out1.innovationNumber, 1.0f, true);
    Connection con2(4, in2.innovationNumber, out1.innovationNumber, 1.0f, true);
    out1.incomingConnections.push_back(3);
    out1.incomingConnections.push_back(4);

    std::unordered_map<int, Neuron> neuronMap = {
            {in1.innovationNumber, in1},
            {in2.innovationNumber, in2},
            {out1.innovationNumber, out1}
    };

    std::unordered_map<int, Connection> connectionMap = {
            {con1.innovationNumber, con1},
            {con2.innovationNumber, con2},
    };
    std::vector<int> inputs = {0, 1};
    std::vector<int> outputs = {2};

    NeatSquared::Network n1(connectionMap, neuronMap, inputs, outputs);
    GraphicsManager::getInstance().networkRenderer.currentNetwork = &n1;

    printf("got to end of starting thread\n");
    // Halt NEAT Thread so networks do not get destroyed yet until main gui thread is done
    while(1){
        ;
    }
}

int main(int, char **) {
//    printf("in main\n");
    std::thread t1(NEATThread);

    startGraphics();

    return 0;
}
