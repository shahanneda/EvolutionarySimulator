//
// Created by Shahan Nedadahandeh on 2022-07-02.
//

#include "SnakeGameRenderer.h"
#include "graphics/GraphicsManager.h"

#include <algorithm>
#include "imgui.h"

using namespace NeatSquared;

SnakeGameRenderer::SnakeGameRenderer() {
}

void SnakeGameRenderer::renderWindow(const ImGuiIO &io) {
    // if game is null, we are not playing snake and should not render renderer for snake
    if (game == nullptr) {
        return;
    }
    ImColor snakeColor = ImColor(ImVec4(0, 0, 1, 1));
    ImColor backgroundColor = ImColor(ImVec4(0.86f, 0.86f, 0.86f, 1));
    ImColor foodColor = ImColor(ImVec4(1, 0, 0, 1));


    float windowWidth = io.DisplaySize.x * 0.15f;
    float windowHeight = io.DisplaySize.y * 0.4f;

    boxSizing = std::min(windowWidth, windowHeight) / SnakeGame::BOARD_SIZE;

    ImGui::SetNextWindowSize({windowWidth, windowHeight}, ImGuiCond_Always);
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.5f, 0});
    ImGui::Begin("Snake", NULL, GraphicsManager::DEFAULT_WINDOW_FLAGS);
    {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        for (int x = 0; x < SnakeGame::BOARD_SIZE; x++) {
            for (int y = 0; y < SnakeGame::BOARD_SIZE; y++) {
                SnakeGame::TileType type = game->getBoardPos({x, y});
                switch (type) {
                    case SnakeGame::EMPTY:
                        renderTile({x, y}, backgroundColor, windowPos, drawList);
                        break;
                    case SnakeGame::FOOD:
                        renderTile({x, y}, foodColor, windowPos, drawList);
                        break;
                    case SnakeGame::SNAKE:
                        renderTile({x, y}, snakeColor, windowPos, drawList);
                        break;
                }
            }
        }
    }
    ImGui::End();
}

void
SnakeGameRenderer::renderTile(SnakeGame::BoardPosition pos, ImColor color, ImVec2 windowPos, ImDrawList *drawList) {
    drawList->AddRectFilled(
            ImVec2(windowPos.x + pos.x * boxSizing, windowPos.y + (pos.y + 1) * boxSizing),
            ImVec2(windowPos.x + (pos.x + 1) * boxSizing, windowPos.y + (pos.y + 2) * boxSizing),
            color);

}
