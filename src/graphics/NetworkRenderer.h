//
// Created by Shahan Nedadahandeh on 2022-05-23.
//


#ifndef NETWORKRENDERER_H
#define NETWORKRENDERER_H


#include "imgui.h"
#include "network/Connection.h"
#include "network/Neuron.h"
#include "network/NetworkInstance.h"

#include <deque>
#include <mutex>
#include <unordered_map>


namespace NeatSquared {

    class NetworkRenderer {
    public:
        NetworkRenderer();

        void renderNetwork();



        NeatSquared::NetworkInstance *currentNetwork;
        std::mutex currentNetworkMutex;


    private:
        static const ImColor nodeColor;
        static const ImColor connectionColor;
        ImDrawList *drawList;
        ImVec2 windowPos;


        void renderConnections(std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap,
                               std::vector<Connection *> &connectionsToRender);

        void
        renderNeurons(std::deque<Neuron *> &neuronsToRender, std::vector<Connection *> &connectionsToRender,
                      int spacing,
                      int startY, int startX, std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap);

        /*
         * Convert ImVec2 position from local to global.
         */
        ImVec2 convertLocalToWindowPos(ImVec2 pos);

        /*
         * Render a neuron. Pos is relative to current window.
         */
        void renderNeuronAtPosition(ImVec2 pos, std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap, Neuron * neuron );

        void renderInputs(int spacing, int inputStartX, int inputStartY,
                                                      std::unordered_map<int, ImVec2> &innovationNumberToNeuronPositionMap);
    };
};


#endif //NETWORKRENDERER_H
