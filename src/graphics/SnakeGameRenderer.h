//
// Created by Shahan Nedadahandeh on 2022-07-02.
//

#include "game/SnakeGame.h"
#include "imgui.h"

#ifndef SNAKEGAMERENDERER_H
#define SNAKEGAMERENDERER_H


namespace NeatSquared {
    class SnakeGameRenderer {
    public:
        SnakeGameRenderer();

        SnakeGame *game;

        void renderWindow();

        constexpr const static float boxSizing = 20.0f;


        void renderTile(SnakeGame::BoardPosition pos, ImColor color, ImVec2 windowPos, ImDrawList *drawList);
    };
};


#endif //SNAKEGAMERENDERER_H
