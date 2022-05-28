//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "NetworkRenderer.h"

#include <deque>

using namespace NeatSquared;

#include "network/Neuron.h"
#include "network/NetworkInstance.h"
#include "imgui.h"

#include <iostream>
#include <mutex>


NetworkRenderer::NetworkRenderer() : currentNetwork(nullptr) {

}

const ImColor NetworkRenderer::nodeColor = ImColor(ImVec4(1, 1, 1, 1));
const ImColor NetworkRenderer::connectionColor = ImColor(ImVec4(1, 1, 1, 1));

void NetworkRenderer::renderNetwork() {
    if (!currentNetwork) {
        ImGui::Begin("Network Renderer");
        {
            ImGui::Text("No network selected");
        }
        ImGui::End();
        return;
    }

    std::lock_guard<std::mutex> lock(currentNetworkMutex);

    std::deque<Neuron *> neuronsToRender;
    for (int innovationNumber: currentNetwork->outputs) {
        Neuron* n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if(n == nullptr) {
            throw std::runtime_error("Innovation number of output neuron not found in innovationToNeuronMap!!");
        }
        neuronsToRender.push_back(n);
    }



    ImGui::Begin("New Window");
    {
        windowPos = ImGui::GetWindowPos();
        drawList = ImGui::GetWindowDrawList();

        const int spacing = 100;
        const int outputStartX = 150;
        const int outputStartY = 100;

        const int inputStartX = 50;
        const int inputStartY = 50;


        std::vector<Connection *> connectionsToRender;
        std::unordered_map<int, ImVec2> innovationNumberToNeuronPositionMap;

        renderInputs(spacing, inputStartX, inputStartY,
                                                           innovationNumberToNeuronPositionMap);


        renderNeurons(neuronsToRender, connectionsToRender, spacing, outputStartX, outputStartY,
                      innovationNumberToNeuronPositionMap);

        renderConnections(innovationNumberToNeuronPositionMap,connectionsToRender);


    }

    ImGui::End();
}

void NetworkRenderer::renderInputs(int spacing, int inputStartX, int inputStartY,
                                                               std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap) {
    int inputCount = 0;
    for (int innovationNumber: currentNetwork->inputs) {
        Neuron* n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if(n == nullptr) {
            throw std::runtime_error("Innovation number of output neuron not found in innovationToNeuronMap!!");
        }

        renderNeuronAtPosition(ImVec2(inputStartX, inputStartY + inputCount * spacing), innovationNumberToNeuronPositionMap, n);
        inputCount++;
    }
}


void
NetworkRenderer::renderNeurons(std::deque<Neuron *> &neuronsToRender, std::vector<Connection *> &connectionsToRender,
                               int spacing, int startX, int startY,
                               std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap) {
    // bfs
    int layerNumber = 5;
    while(!neuronsToRender.empty()){
        auto layerCount = neuronsToRender.size();

        for(std::deque<Neuron *>::size_type i = 0; i < layerCount; i++){
            Neuron* n = neuronsToRender.front();
            if(n == nullptr){
                std::runtime_error("trying to render neuron which is not in newtork!! ");
            }

            neuronsToRender.pop_front();


            // accesign neuron which is expired
            if(innovationNumberToNeuronPositionMap.find(n->innovationNumber) != innovationNumberToNeuronPositionMap.end()){
                continue;
            }

            ImVec2 pos = ImVec2(startX+layerNumber*spacing, startY + i * spacing);
            renderNeuronAtPosition(pos, innovationNumberToNeuronPositionMap, n);


            // add next layers neurons
            for (int innovationNumber: n->incomingConnections) {
                Connection* c = currentNetwork->getConnectionWithInnovationNumber(innovationNumber);

                if(c == nullptr) {
                    throw std::runtime_error("NetworkRenderer: Innovation number of connection not found in innovationToConnection map!! #: " + std::to_string(innovationNumber));
                }
                neuronsToRender.push_back(currentNetwork->getNeuronWithInnovationNumber(c->from));
                connectionsToRender.push_back(c);
            }


        }
        layerNumber--;
    }
}

void NetworkRenderer::renderConnections(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap, std::vector<Connection *> &connectionsToRender){
    for(Connection* c : connectionsToRender){
        float thickness = (c->weight + 2) * 1;

        // just for debugging weight breeding, not actual color system
        ImColor color;
        if(c->weight > 0.5){
            color = ImColor(ImVec4(1, 0, 0, 1));
        }else{
            color = ImColor(ImVec4(0, 1, 0, 1));
        }

        drawList->AddLine(convertLocalToWindowPos(innovationNumberToNeuronPositionMap[c->from]), convertLocalToWindowPos(innovationNumberToNeuronPositionMap[c->to]), color, thickness);
    }

}

void NetworkRenderer::renderNeuronAtPosition(ImVec2 pos, std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap, Neuron * neuron ) {
    const int nodeRadius = 10;
    drawList->AddCircleFilled(convertLocalToWindowPos(pos), nodeRadius, nodeColor, 0);
    innovationNumberToNeuronPositionMap[neuron->innovationNumber] = pos;
}

ImVec2 NetworkRenderer::convertLocalToWindowPos(ImVec2 pos){
    return ImVec2(windowPos.x + pos.x, windowPos.y + pos.y);
}





