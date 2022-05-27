#include <unordered_map>
#include <thread>
#include <iostream>
#include "network/Neuron.h"
#include "graphics/GraphicsManager.h"
#include "network/Connection.h"
#include "network/NetworkInstance.h"
#include "utils/RandomGenerator.h"
#include "network/NetworkBreeder.h"



using namespace NeatSquared;
void startGraphics()
{
    GraphicsManager::getInstance().startMainLoop();
    std::cout << "hello" << std::endl;
}

void NEATThread(){
    printf("Trying to start thread\n");


    // just for testing threading
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Neuron in1(0);
    Neuron in2(1);
    Neuron out1(2);
    Neuron h1(3);

    Neuron h2(100);
    Neuron h3(101);

    Connection con1(4, in1.innovationNumber, h1.innovationNumber, 1.0f, true);
    Connection con2(5, in2.innovationNumber, h1.innovationNumber, 1.0f, true);
    Connection con3(6, h1.innovationNumber, out1.innovationNumber, 2.0f, true);
    Connection con4(7, in1.innovationNumber, out1.innovationNumber, 0.1f, true);


//    in1.addConnection(&con1);
//    in2.addConnection(&con2);
//
//    h1.addConnection(&con1);
//    h1.addConnection(&con2);
//    h1.addConnection(&con3);
//
//    out1.addConnection(&con4);
//    out1.addConnection(&con3);


    NetworkInstance n1({in1, in2, h1, out1}, {con1, con2, con3, con4});

//    Connection con5(8, in1.innovationNumber, h2.innovationNumber, 0.1f, true);



    NetworkInstance n2({in1, in2, h1, out1}, {con1, con2, con3, con4});

    std::unique_ptr<NetworkInstance> breed1 = NetworkBreeder::Crossover(&n1, &n2);


    GraphicsManager::getInstance().networkRenderer.currentNetwork = breed1.get();
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
