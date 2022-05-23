//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#include "NetworkRenderer.h"

using namespace NeatSquared;

#include "imgui.h"

NetworkRenderer::NetworkRenderer() : currentNetwork(nullptr) {

}

const ImColor NetworkRenderer::nodeColor = ImColor(ImVec4(1,1,1,1));
const ImColor NetworkRenderer::connectionColor = ImColor(ImVec4(1,1,1,1));

void NetworkRenderer::renderNetwork() {
    if(!currentNetwork){
        ImGui::Begin("Network Renderer");
        {
            ImGui::Text("No network selected");
        }
        ImGui::End();
        return;
    }


    ImGui::Begin("New Window");
    {
        ImVec2 pos = ImGui::GetWindowPos();
        ImGui::Text("New window testing!!");
        auto drawList = ImGui::GetWindowDrawList();
        drawList->AddCircleFilled(ImVec2(pos.x, pos.y), 10 , nodeColor, 0);
        for (int i = 0; i < 10; i++) {
            drawList->AddCircleFilled(ImVec2(pos.x + 50 + 100 * i, pos.y + 100), 10 + 5 * i, connectionColor, 0);
        }
    }
    ImGui::End();
}






