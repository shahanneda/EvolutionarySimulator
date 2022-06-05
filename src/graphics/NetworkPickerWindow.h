//
// Created by Shahan Nedadahandeh on 2022-06-04.
//
#include "evolution/Generation.h"

#ifndef NETWORKPICKER_H
#define NETWORKPICKER_H


namespace NeatSquared {
    class NetworkPickerWindow {
    public:
        void renderWindow();

        std::vector<Generation> *generations;
    };
}


#endif //NETWORKPICKER_H
