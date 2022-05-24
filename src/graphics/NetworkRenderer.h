//
// Created by Shahan Nedadahandeh on 2022-05-23.
//


#ifndef NETWORKRENDERER_H
#define NETWORKRENDERER_H


#include "imgui.h"
#include "network/Network.h"
#include <unordered_map>

namespace NeatSquared {

    class NetworkRenderer {
    public:
        NetworkRenderer();

        void renderNetwork();
        /*
         * Render a neuron. Pos is relative to current window.
         */
        void renderNeuronAtPosition(ImVec2 pos);

        NeatSquared::Network *currentNetwork;


    private:
        static const ImColor nodeColor;
        static const ImColor connectionColor;
        ImDrawList* drawList;
        ImVec2 windowPos;


    };
}


#endif //NETWORKRENDERER_H
