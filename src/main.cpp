#include <unordered_map>
#include <thread>
#include <iostream>
#include "graphics/GraphicsManager.h"
#include "network/Neuron.h"
#include "network/NetworkInstance.h"
#include "utils/RandomGenerator.h"


class Neuron;

using namespace NeatSquared;
void startGraphics()
{
    GraphicsManager::getInstance().startMainLoop();
    std::cout << "hello" << std::endl;
}

void NEATThread(){
    printf("Trying to start thread\n");

    RandomGenerator::init();

    // just for testing threading
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Neuron in1(0);
    Neuron in2(1);
    Neuron h1(2);
    Neuron out1(5);

    Connection con1(3, in1.innovationNumber, h1.innovationNumber, 1.0f, true);
    Connection con2(4, in2.innovationNumber, h1.innovationNumber, 1.0f, true);
    Connection con3(6, h1.innovationNumber, out1.innovationNumber, 2.0f, true);
    Connection con4(7, in1.innovationNumber, out1.innovationNumber, 0.1f, true);

    h1.addConnection(&con1);
    h1.addConnection(&con2);
    out1.addConnection(&con4);
    out1.addConnection(&con3);



    std::vector<int> inputs = {in1.innovationNumber, in2.innovationNumber};
    std::vector<int> outputs = {out1.innovationNumber};

    NetworkInstance n1({in1, in2, h1, out1}, {con1, con2, con3, con4}, inputs, outputs);

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
