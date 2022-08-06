//
// Created by Shahan Nedadahandeh on 2022-06-04.
//

#ifndef NETWORKPICKER_H
#define NETWORKPICKER_H

#include "evolution/Generation.h"
#include "graphics/GraphicsWindow.h"


namespace NeatSquared {
    class NetworkPickerWindow : public GraphicsWindow {
    public:
        NetworkPickerWindow();

        // have to use int for selected generation, since the generations are stored in a vector and references to vectors can change as the vector grows/shrinks

        int selectedGenerationId;
        const Species *selectedSpecies;
        NetworkInstance *selectedNetwork;

        void renderWindow(const ImGuiIO &io) override;

        bool beginListBox(const char *id);

        void changeRenderingNetwork(NetworkInstance &network);
    };
}


#endif //NETWORKPICKER_H
