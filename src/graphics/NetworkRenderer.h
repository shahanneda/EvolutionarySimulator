//
// Created by Shahan Nedadahandeh on 2022-05-23.
//


#ifndef NETWORKRENDERER_H
#define NETWORKRENDERER_H


#include "imgui.h"
#include "network/Connection.h"
#include "network/Neuron.h"
#include "network/NetworkInstance.h"
#include "graphics/GraphicsWindow.h"

#include <deque>
#include <mutex>
#include <unordered_map>


namespace NeatSquared {

    class NetworkRenderer : public GraphicsWindow {
    public:
        NetworkRenderer();

        NeatSquared::NetworkInstance *currentNetwork;
        std::mutex currentNetworkMutex;

        ImVec2 displayOffset;
        bool displayNeuronInnovationNumber;
        bool displayConnectionInnovationNumber;
        bool displayConnectionWeight;

        void renderWindow(const ImGuiIO &io) override;

    private:
        static const ImColor nodeColor;
        static const ImColor connectionColor;
        static const ImColor grayColor;
        static const ImColor activeColor;
        static const ImColor negativeActiveColor;

        ImDrawList *drawList;
        ImVec2 windowPos;


        /*
         * Convert ImVec2 position from local to global.
         */
        ImVec2 convertLocalToWindowPos(ImVec2 pos);

        /*
         * Render a neuron. Pos is relative to current window.
         */
        void renderNeuronAtPosition(ImVec2 pos, Neuron *neuron);


        /*
         * Render neurons to the screen
         */
        void renderNeurons(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap);

        /*
         * Render connections to the screen
         */
        void renderConnections(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                               std::unordered_map<int, Connection *> &connectionsToRender);


        /*
         * Precalculate the positions of the neurons
         */
        void
        calculateNeuronPositions(int horizontalSpacing, int verticalSpacing, int startX, int startY, int maxLayerNumber,
                                 std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                 std::deque<Neuron *> &neuronsToRender,
                                 std::unordered_map<int, Connection *> &connectionsToRender);

        /*
         * Calcualte the position of the input neurons
         */
        void calculateInputPositions(int spacing, int inputStartX, int inputStartY,
                                     std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                                     std::unordered_map<int, Connection *> &connectionsToRender);


        /*
         * Populate all connections in the vector into the connections to render map
         */
        void addConnectionsToRender(std::vector<int> &connectionInnovationNumbers,
                                    std::unordered_map<int, Connection *> &connectionsToRender) const;


        void renderConnectionTriangle(ImVec2 conStart, ImVec2 conEnd, ImU32 color);

        /*
         * Get color from neuron activation value.
         */
        ImU32 getColorFromValue(float value);
    };

}

#endif //NETWORKRENDERER_H
