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

        // have to use int for selected generation, since the generations are stored in a vector and references to vectors can change as the vector grows/shrinks

        int selectedGenerationId;
        const Species *selectedSpecies;
        NetworkInstance *selectedNetwork;

        bool beginListBox(const char *id);

        void changeRenderingNetwork(NetworkInstance &network);
    };
}


#endif //NETWORKPICKER_H
