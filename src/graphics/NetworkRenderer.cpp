//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "NetworkRenderer.h"

#include <deque>

using namespace NeatSquared;

#include "network/Neuron.h"
#include "network/Network.h"
#include <iostream>

#include "imgui.h"

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


    std::deque<Neuron *> neuronsToRender;
    for (int innovationNumber: currentNetwork->outputs) {
        Neuron* n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if(n == nullptr) {
            throw std::runtime_error("Innovation number of input neuron not found in innovationToNeuronMap!!");
        }
        neuronsToRender.push_back(n);
    }


    std::vector<Connection *> connectionsToRender;
    ImGui::Begin("New Window");
    {
        windowPos = ImGui::GetWindowPos();
        drawList = ImGui::GetWindowDrawList();

        int spacing = 100;
        int startY = 100;
        int startX = 100;

        std::cout << " size: " << neuronsToRender.size() << std::endl;

        // bfs
        int layerNumber = 0;

        std::unordered_map<int, ImVec2> innovationNumberToNeuronPositionMap;
        while(!neuronsToRender.empty()){
            auto layerCount = neuronsToRender.size();
            for(std::deque<NeatSquared::Neuron *>::size_type i = 0; i < layerCount; i++){
                Neuron* n = neuronsToRender.front();
                neuronsToRender.pop_front();


                if(innovationNumberToNeuronPositionMap.find(n->innovationNumber) != innovationNumberToNeuronPositionMap.end()){
                    continue;
                }

                ImVec2 pos = ImVec2(startX+layerNumber*spacing, startY + i * spacing);
                renderNeuronAtPosition(pos);
                innovationNumberToNeuronPositionMap[n->innovationNumber] = pos;

                std::cout << " i  is" << i << std::endl;

                // add next layers neurons
                for (int innovationNumber: n->incomingConnections) {
                    Connection* c = currentNetwork->getConnectionWithInnovationNumber(innovationNumber);

                    if(c == nullptr) {
                        throw std::runtime_error("Innovation number of connection not found in innovationToConnectionap!!");
                    }
                    neuronsToRender.push_back(currentNetwork->getNeuronWithInnovationNumber(c->in));
                    connectionsToRender.push_back(c);
                }


            }
            layerNumber++;
        }

    }

    ImGui::End();
}

void NetworkRenderer::renderNeuronAtPosition(ImVec2 pos) {
    std::cout << "calling at " << pos.x  << " " << pos.y << std::endl;
    const int nodeRadius = 10;
    drawList->AddCircleFilled(ImVec2(windowPos.x + pos.x, windowPos.y + pos.y), nodeRadius, nodeColor, 0);
}






