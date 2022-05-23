#include <unordered_map>
#include "graphics/GraphicsManager.h"
#include "network/Neuron.h"
#include "network/Network.h"

int main(int, char **) {
    GraphicsManager::getInstance().startMainLoop();

    Neuron in1(0);
    Neuron in2(1);
    Neuron out1(2);

    Connection con1(3, in1.innovationNumber, out1.innovationNumber, 1.0f, true);
    Connection con2(4, in2.innovationNumber, out1.innovationNumber, 1.0f, true);

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

    Network n1(connectionMap, neuronMap, inputs);



    return 0;
}
