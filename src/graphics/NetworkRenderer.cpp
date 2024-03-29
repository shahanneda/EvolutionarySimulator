//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "NetworkRenderer.h"

#include <deque>

using namespace NeatSquared;

#include "network/Neuron.h"
#include "network/NetworkInstance.h"
#include "GraphicsManager.h"

#include <iostream>
#include <mutex>
#include <string>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iomanip>

#include "imgui.h"
#include "glm/gtx/rotate_vector.hpp"
#include <glm/glm.hpp>

using std::vector;

NetworkRenderer::NetworkRenderer() : currentNetwork(nullptr), displayOffset(0, 0),
                                     displayNeuronInnovationNumber(false), displayConnectionInnovationNumber(false) {

}

const ImColor NetworkRenderer::nodeColor = ImColor(ImVec4(1, 1, 1, 1));
const ImColor NetworkRenderer::connectionColor = ImColor(ImVec4(1, 1, 1, 1));
const ImColor NetworkRenderer::grayColor = ImColor(ImVec4(0.86f, 0.86f, 0.86f, 1));
const ImColor NetworkRenderer::activeColor = ImColor(ImVec4(0, 1.0f, 0, 1));
const ImColor NetworkRenderer::negativeActiveColor = ImColor(ImVec4(1.0f, 0, 0, 1));

void NetworkRenderer::renderWindow(const ImGuiIO &io) {
    if (!currentNetwork) {
        ImGui::Begin("Network Renderer");
        {
            ImGui::Text("No network selected");
        }
        ImGui::End();
        return;
    }

    std::lock_guard<std::mutex> lock(currentNetworkMutex);

    // for inspecting networks manually this is needed, but not for auto evaluation
    // currentNetwork->evaluateNetwork();

    std::deque<Neuron *> neuronsToRender;
    for (int innovationNumber: currentNetwork->outputs) {
        Neuron *n = currentNetwork->getNeuronWithInnovationNumber(innovationNumber);
        if (n == nullptr) {
            throw std::runtime_error("Innovation number of output neuron not found in innovationToNeuronMap!!");
        }
        neuronsToRender.push_back(n);
    }


    ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y * 0.6f}, ImGuiCond_Always);
    ImGui::SetNextWindowPos({0, io.DisplaySize.y * 0.4f});
    ImGui::Begin("Network Renderer", NULL,
                 GraphicsManager::DEFAULT_WINDOW_FLAGS);
    {
        windowPos = ImGui::GetWindowPos();
        drawList = ImGui::GetWindowDrawList();

        const int verticalSpacing = 50;
        const int horizontalSpacing = 100;

        const int outputStartX = ImGui::GetWindowWidth() / 2;
        const int outputStartY = 100;

        const int inputStartX = 50;
        const int inputStartY = 50;
        const int maxLayerNumber = 4;


        std::unordered_map<int, ImVec2> innovationNumberToNeuronPositionMap;
        std::unordered_map<int, Connection *> connectionsToRender;

        calculateInputPositions(verticalSpacing * 2, inputStartX, inputStartY, innovationNumberToNeuronPositionMap,
                                connectionsToRender);

        calculateNeuronPositions(horizontalSpacing, verticalSpacing, outputStartX, outputStartY, maxLayerNumber,
                                 innovationNumberToNeuronPositionMap,
                                 neuronsToRender, connectionsToRender);
        renderConnections(innovationNumberToNeuronPositionMap, connectionsToRender);
        renderNeurons(innovationNumberToNeuronPositionMap);
    }

    ImGui::End();
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
                                               int maxLayerNumber,
                                               std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                               std::deque<Neuron *> &neuronsToRender,
                                               std::unordered_map<int, Connection *> &connectionsToRender) {
    // bfs
    int layerNumber = maxLayerNumber;
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
        float thickness = fmin(abs(c->weight) * 2 + 1, 5.0f);

        // just for debugging weight breeding, not actual color system
        ImColor connectionColor = getColorFromValue(c->lastCalculatedValue);
        if (!c->enabled) {
            connectionColor = grayColor;
        }

        ImVec2 p1 = innovationNumberToNeuronPositionMap[c->from];
        ImVec2 p2 = innovationNumberToNeuronPositionMap[c->to];

        drawList->AddLine(convertLocalToWindowPos(p1),
                          convertLocalToWindowPos(p2), connectionColor, thickness);

        renderConnectionTriangle(p1, p2, connectionColor);


        int xTextOffset = -4;
        int yTextOffset = -8;
        ImVec2 textPos = ImVec2((p1.x + p2.x) / 2 + xTextOffset, (p1.y + p2.y) / 2 + yTextOffset);
        const ImU32 textColor = ImColor(ImVec4(1, 1, 1, 1));
        if (displayConnectionInnovationNumber) {
            drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                              std::to_string(c->innovationNumber).c_str());
        } else if (displayConnectionWeight) {
            drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                              std::to_string(c->weight).c_str());
        }
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

ImU32 NetworkRenderer::getColorFromValue(float value) {
    value = (value + 1) / 2; // shift from t expected (-1,1) to (0, 1)
    value = fmax(0, fmin(1, value)); // clamp value between 0 and 1
    float distanceToActive = value;
    float distanceToNegative = 1 - value;

    return ImColor(
            ImVec4(distanceToActive * activeColor.Value.x + distanceToNegative * negativeActiveColor.Value.x,
                   distanceToActive * activeColor.Value.y + distanceToNegative * negativeActiveColor.Value.y,
                   distanceToActive * activeColor.Value.z + distanceToNegative * negativeActiveColor.Value.z,
                   1));

}

void NetworkRenderer::renderNeuronAtPosition(ImVec2 pos,
                                             Neuron *neuron) {
    const int nodeRadius = 10;


    drawList->AddCircleFilled(convertLocalToWindowPos(pos), nodeRadius, getColorFromValue(neuron->currentValue), 0);

    if (displayNeuronInnovationNumber) {
        ImVec2 textPos = ImVec2(pos.x - 3, pos.y - 8);

        const ImU32 textColor = ImColor(ImVec4(0, 0, 0, 1));
        drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                          std::to_string(neuron->innovationNumber).c_str());
    } else {
        ImVec2 textPos = ImVec2(pos.x - 8, pos.y + 8);
        const ImU32 textColor = ImColor(ImVec4(1, 1, 1, 1));

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << neuron->currentValue;
        std::string text = ss.str();

        drawList->AddText(NULL, 15.0f, convertLocalToWindowPos(textPos), textColor,
                          text.c_str());
    }

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





