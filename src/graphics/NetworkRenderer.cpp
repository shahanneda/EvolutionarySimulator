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
#include <string>
#include <unordered_set>

#include "glm/gtx/rotate_vector.hpp"
#include <glm/glm.hpp>

using std::vector;

NetworkRenderer::NetworkRenderer() : currentNetwork(nullptr), displayOffset(0, 0) {

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
        Neuron *n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if (n == nullptr) {
            throw std::runtime_error("Innovation number of output neuron not found in innovationToNeuronMap!!");
        }
        neuronsToRender.push_back(n);
    }


    ImGui::Begin("New Window");
    {
        windowPos = ImGui::GetWindowPos();
        drawList = ImGui::GetWindowDrawList();

        const int verticalSpacing = 50;
        const int horizontalSpacing = 50;

//        printf("dith %.2f \n", ImGui::GetWindowWidth());
        const int outputStartX = ImGui::GetWindowWidth() / 2;
        const int outputStartY = 100;

        const int inputStartX = 50;
        const int inputStartY = 50;


        std::unordered_map<int, ImVec2> innovationNumberToNeuronPositionMap;
        std::unordered_map<int, Connection *> connectionsToRender;

        calculateInputPositions(verticalSpacing, inputStartX, inputStartY, innovationNumberToNeuronPositionMap,
                                connectionsToRender);

        calculateNeuronPositions(horizontalSpacing, verticalSpacing, outputStartX, outputStartY,
                                 innovationNumberToNeuronPositionMap,
                                 neuronsToRender, connectionsToRender);
        renderConnections(innovationNumberToNeuronPositionMap, connectionsToRender);
        renderNeurons(innovationNumberToNeuronPositionMap);
    }

    ImGui::End();
}

void NetworkRenderer::handleInput() {
    const float speed = 5.0f;
    if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) {
        displayOffset = ImVec2(displayOffset.x - speed, displayOffset.y);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) {
        displayOffset = ImVec2(displayOffset.x + speed, displayOffset.y);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
        displayOffset = ImVec2(displayOffset.x, displayOffset.y + speed);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
        displayOffset = ImVec2(displayOffset.x, displayOffset.y - speed);
    }
}

void NetworkRenderer::calculateInputPositions(int spacing, int inputStartX, int inputStartY,
                                              std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                              std::unordered_map<int, Connection *> &connectionsToRender) {

    int inputCount = 0;
    for (int innovationNumber: currentNetwork->inputs) {
        Neuron *n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if (n == nullptr) {
            throw std::runtime_error("Innovation number of output neuron not found in innovationToNeuronMap!!");
        }

        innovationNumberToNeuronPositionMap[n->innovationNumber] = ImVec2(inputStartX,
                                                                          inputStartY + inputCount * spacing);
        inputCount++;
        addConnectionsToRender(n->outgoingConnections, connectionsToRender);
        addConnectionsToRender(n->incomingConnections, connectionsToRender);
    }
}

void NetworkRenderer::addConnectionsToRender(vector<int> &connectionInnovationNumbers,
                                             std::unordered_map<int, Connection *> &connectionsToRender) const {
    for (int innovationNumber: connectionInnovationNumbers) {
        if (connectionsToRender.count(innovationNumber) > 0) {
            continue;
        }

        Connection *c = currentNetwork->getConnectionWithInnovationNumber(innovationNumber);
        if (c == nullptr) {
            throw std::runtime_error(
                    "NetworkRenderer: Innovation number of connection not found in innovationToConnection map!! #: " +
                    std::to_string(innovationNumber));
        }

        connectionsToRender.insert({innovationNumber, c});
    }
}


void NetworkRenderer::calculateNeuronPositions(int horizontalSpacing, int verticalSpacing, int startX, int startY,
                                               std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                               std::deque<Neuron *> &neuronsToRender,
                                               std::unordered_map<int, Connection *> &connectionsToRender) {
    // bfs
    int layerNumber = 10;
    while (!neuronsToRender.empty()) {
        auto layerCount = neuronsToRender.size();

        for (std::deque<Neuron *>::size_type i = 0; i < layerCount; i++) {
            Neuron *n = neuronsToRender.front();
            if (n == nullptr) {
                throw std::runtime_error("trying to render neuron which is not in newtork!! ");
            }

            neuronsToRender.pop_front();

            if (innovationNumberToNeuronPositionMap.find(n->innovationNumber) !=
                innovationNumberToNeuronPositionMap.end()) {
                continue;
            }

            ImVec2 pos = ImVec2(startX + layerNumber * horizontalSpacing, startY + i * verticalSpacing);
            innovationNumberToNeuronPositionMap[n->innovationNumber] = pos;


            // add next layers neurons
            for (int innovationNumber: n->incomingConnections) {
                Connection *c = currentNetwork->getConnectionWithInnovationNumber(innovationNumber);

                if (c == nullptr) {
                    throw std::runtime_error(
                            "NetworkRenderer: Innovation number of connection not found in innovationToConnection map!! #: " +
                            std::to_string(innovationNumber));
                }
                neuronsToRender.push_back(currentNetwork->getNeuronWithInnovationNumber(c->from));
            }

            // add previous layers as well, because of connections flips some are missed
            for (int innovationNumber: n->outgoingConnections) {
                Connection *c = currentNetwork->getConnectionWithInnovationNumber(innovationNumber);

                if (c == nullptr) {
                    throw std::runtime_error(
                            "NetworkRenderer: Innovation number of connection not found in innovationToConnection map!! #: " +
                            std::to_string(innovationNumber));
                }
                neuronsToRender.push_back(currentNetwork->getNeuronWithInnovationNumber(c->to));
            }


            addConnectionsToRender(n->incomingConnections, connectionsToRender);
            addConnectionsToRender(n->outgoingConnections, connectionsToRender);
        }
        layerNumber--;
    }
}

void NetworkRenderer::renderConnections(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                        std::unordered_map<int, Connection *> &connectionsToRender) {
    for (auto it: connectionsToRender) {
        Connection *c = it.second;
        float thickness = (c->weight + 2) * 1;

        // just for debugging weight breeding, not actual color system
        ImColor arrowColor;
        ImColor color;
        if (c->weight > 0.5) {
            color = ImColor(ImVec4(1, 0, 0, 1));
            arrowColor = ImColor(ImVec4(0.8, 0.1, 0, 1));
        } else {
            color = ImColor(ImVec4(0, 1, 0, 1));
            arrowColor = ImColor(ImVec4(0.1, 0.8, 0, 1));
        }

        ImVec2 p1 = innovationNumberToNeuronPositionMap[c->from];
        ImVec2 p2 = innovationNumberToNeuronPositionMap[c->to];

        drawList->AddLine(convertLocalToWindowPos(p1),
                          convertLocalToWindowPos(p2), color, thickness);

        renderConnectionTriangle(p1, p2, arrowColor);

        int xTextOffset = -4;
        int yTextOffset = -8;
        ImVec2 textPos = ImVec2((p1.x + p2.x) / 2 + xTextOffset, (p1.y + p2.y) / 2 + yTextOffset);
        const ImU32 textColor = ImColor(ImVec4(1, 1, 1, 1));

        drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                          std::to_string(c->innovationNumber).c_str());
    }

}

void NetworkRenderer::renderNeurons(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap) {
    for (const auto &it: innovationNumberToNeuronPositionMap) {
        Neuron *n = currentNetwork->getNeuronWithInnovationNumber(it.first);
        if (n == nullptr) {
            throw std::runtime_error("Innovation number of neuron not found in innovationToNeuronMap!!");
        }

        renderNeuronAtPosition(it.second, n);
    }
}

void NetworkRenderer::renderNeuronAtPosition(ImVec2 pos,
                                             Neuron *neuron) {
    const int nodeRadius = 10;
    ImVec2 textPos = ImVec2(pos.x - 3, pos.y - 8);

    const ImU32 textColor = ImColor(ImVec4(0, 0, 0, 1));

    drawList->AddCircleFilled(convertLocalToWindowPos(pos), nodeRadius, nodeColor, 0);
    drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                      std::to_string(neuron->innovationNumber).c_str());
}

void NetworkRenderer::renderConnectionTriangle(ImVec2 conStart, ImVec2 conEnd, ImU32 color) {
    float rotationAngle = 25.0f;
    float topDownDistance = 10.0f;
    float sidesDownDistance = 15.0f;

    glm::vec2 vec(conEnd.x - conStart.x, conEnd.y - conStart.y);
    glm::vec2 norm = glm::normalize(vec);
    vec = vec - norm * topDownDistance;


    ImVec2 p1 = ImVec2(conStart.x + vec.x, conStart.y + vec.y);

    glm::vec2 top = glm::rotate(-glm::normalize(vec), glm::radians(rotationAngle)) * sidesDownDistance;
    ImVec2 p2(p1.x + top.x, p1.y + top.y);

    glm::vec2 bottom = glm::rotate(-glm::normalize(vec), glm::radians(-rotationAngle)) * sidesDownDistance;
    ImVec2 p3(p1.x + bottom.x, p1.y + bottom.y);


    drawList->AddTriangleFilled(convertLocalToWindowPos(p1), convertLocalToWindowPos(p2),
                                convertLocalToWindowPos(p3), color);
}

ImVec2 NetworkRenderer::convertLocalToWindowPos(ImVec2 pos) {
    return ImVec2(windowPos.x + pos.x + displayOffset.x, windowPos.y + pos.y + displayOffset.y);
}





