//
// Created by Shahan Nedadahandeh on 2022-05-23.
//


#ifndef NETWORKRENDERER_H
#define NETWORKRENDERER_H


#include "network/Network.h"
#include "imgui.h"

namespace NeatSquared {
    class NetworkRenderer {
    public:
        NetworkRenderer();

        void renderNetwork();

        Network *currentNetwork;


    private:
        static const ImColor nodeColor;
        static const ImColor connectionColor;


    };
}


#endif //NETWORKRENDERER_H
