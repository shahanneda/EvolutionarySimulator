//
// Created by Shahan Nedadahandeh on 2022-08-06.
//

#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H


#include "imgui.h"

namespace NeatSquared {
    class GraphicsWindow {
        virtual void renderWindow(const ImGuiIO &io) = 0;
    };
}


#endif //GRAPHICSWINDOW_H