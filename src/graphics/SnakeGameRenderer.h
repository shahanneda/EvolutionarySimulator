//
// Created by Shahan Nedadahandeh on 2022-07-02.
//

#ifndef SNAKEGAMERENDERER_H
#define SNAKEGAMERENDERER_H

#include "game/SnakeGame.h"
#include "graphics/GraphicsWindow.h"

#include "imgui.h"

namespace NeatSquared {
    class SnakeGameRenderer : public GraphicsWindow {
    public:
        SnakeGameRenderer();

        SnakeGame *game;

        float boxSizing = 20.0f;

        void renderWindow(const ImGuiIO &io) override;

        void renderTile(SnakeGame::BoardPosition pos, ImColor color, ImVec2 windowPos, ImDrawList *drawList);
    };
};


#endif //SNAKEGAMERENDERER_H
