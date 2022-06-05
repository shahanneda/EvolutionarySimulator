//
// Created by Shahan Nedadahandeh on 2022-06-04.
//
#include "evolution/Generation.h"

#ifndef NETWORKPICKER_H
#define NETWORKPICKER_H


namespace NeatSquared {
    class NetworkPickerWindow {
    public:
        NetworkPickerWindow();

        void renderWindow();

        std::vector<Generation> *generations;
        int selectedGenerationId;
        Species *selectedSpecies;
        NetworkInstance *selectedNetwork;

        bool beginListBox(const char *id);

        void changeRenderingNetwork(NetworkInstance &network);
    };
}


#endif //NETWORKPICKER_H
