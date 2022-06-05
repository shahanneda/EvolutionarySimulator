//
// Created by Shahan Nedadahandeh on 2022-06-04.
//


#include "NetworkPickerWindow.h"
#include "graphics/GraphicsManager.h"

#include <string>
#include <format>
#include <iomanip>
#include <sstream>
#include <mutex>
#include "imgui.h"


using namespace NeatSquared;


NetworkPickerWindow::NetworkPickerWindow() : selectedGenerationId(0), selectedSpecies(nullptr),
                                             selectedNetwork(nullptr) {}


bool NetworkPickerWindow::beginListBox(const char *id) {
    return ImGui::BeginListBox(id, ImVec2(ImGui::GetWindowContentRegionWidth() * 0.33f,
                                          ImGui::GetWindowHeight()));
}

std::string getLabelString(std::string label, int id, float fitness) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << label << " " << id << " -(f: "
           << fitness << ")";
    return stream.str();
}

void NetworkPickerWindow::renderWindow() {
    if (!generations) {
        return;
    }

    Generation &selectedGeneration = (*generations)[selectedGenerationId];


    ImGui::Begin("Network Picker");
    {
        ImGui::BeginGroup();
        ImGui::Text("Generations");
        if (beginListBox("##Generations")) {
            for (const Generation &g: *generations) {

                const bool is_selected = (g.id == selectedGenerationId);

                if (ImGui::Selectable(getLabelString("Generation", g.id, g.getSumOfAverageSpeciesFitness()).c_str(),
                                      is_selected))
                    selectedGenerationId = g.id;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::EndGroup();


        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("Species");
        if (beginListBox("##Species")) {
            for (Species &s: selectedGeneration.species) {
                const bool is_selected = selectedSpecies && (s.id == selectedSpecies->id);

                if (ImGui::Selectable(getLabelString("Species", s.id, s.averageFitness).c_str(), is_selected))
                    selectedSpecies = &s;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::EndGroup();


        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("Networks");
        if (selectedSpecies && beginListBox("##Networks")) {
            for (NetworkInstance &n: selectedSpecies->networks) {
                const bool is_selected = selectedNetwork && selectedNetwork->id == n.id;

                if (ImGui::Selectable(getLabelString("Network", n.id, n.lastEvaluationFitness).c_str(), is_selected)) {
                    selectedNetwork = &n;
                    changeRenderingNetwork(n);
                }


                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::EndGroup();

    }
    ImGui::End();
}


void NetworkPickerWindow::changeRenderingNetwork(NetworkInstance &network) {
    std::lock_guard<std::mutex>(GraphicsManager::getInstance().networkRenderer.currentNetworkMutex);
    GraphicsManager::getInstance().networkRenderer.currentNetwork = &network;
}



