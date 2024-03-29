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
                                          ImGui::GetWindowHeight() * 0.90f));
}

std::string getLabelString(std::string label, int id, float fitness) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << label << " " << id << " ("
           << fitness << ")";
    return stream.str();
}

void NetworkPickerWindow::renderWindow(const ImGuiIO &io) {
    if (!GraphicsManager::getInstance().breedingManager) {
        return;
    }

    std::vector<Generation> *generations = &GraphicsManager::getInstance().breedingManager->generations;

    if (!generations) {
        return;
    }

    Generation &selectedGeneration = (*generations)[selectedGenerationId];


    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.4f}, ImGuiCond_Always);
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Network Picker", NULL, GraphicsManager::DEFAULT_WINDOW_FLAGS);
    {
        ImGui::BeginGroup();
        ImGui::Text("Generations");
        if (beginListBox("##Generations")) {
            // Show generations in reverse order, also don't show the last generation, since its still training
            for (unsigned long i = generations->size() - 1; i > 0; i--) {
                Generation &g = (*generations)[i - 1];

                const bool is_selected = (g.id == selectedGenerationId);

                if (ImGui::Selectable(getLabelString("Generation", g.id,
                                                     g.getTopSpeciesFitness()).c_str(),
                                      is_selected)) {
                    selectedGenerationId = g.id;

                    // set default selected network if possible
                    if (!g.species.empty()) {
                        selectedSpecies = &g.species[0];
                        if (!selectedSpecies->networks.empty()) {
                            selectedNetwork = &selectedSpecies->networks[0].get();
                            changeRenderingNetwork(*selectedNetwork);
                        }
                    }
                }

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

                if (ImGui::Selectable(getLabelString("Species", s.id, s.averageFitness).c_str(), is_selected)) {
                    selectedSpecies = &s;
                    // set default selected network if possible
                    if (!s.networks.empty()) {
                        selectedNetwork = &selectedSpecies->networks[0].get();
                        changeRenderingNetwork(*selectedNetwork);
                    }
                }

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
    std::lock_guard<std::mutex> networkLock(GraphicsManager::getInstance().networkRenderer.currentNetworkMutex);
    GraphicsManager::getInstance().networkRenderer.currentNetwork = &network;
    GraphicsManager::getInstance().breedingManager->game.shouldTerminateGame = true;

}



