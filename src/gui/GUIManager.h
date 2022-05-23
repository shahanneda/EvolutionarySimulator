//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

class GUIManager {
private:
    char *glslVersion;
    SDL_Window *window;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool shouldCloseGui = false;
    SDL_GLContext glContext;

public:
    GUIManager();
    ~GUIManager();
    void startMainLoop();

private:
    void decideGLSLVersion();
    void initSDL();
    void initImGui();

    void mainGUILoop();



    void finishOpenGLRender(const ImGuiIO &io) const;

    void renderMainFrame(const ImGuiIO &io);

    void pollSTL();
};


#endif //GUIMANAGER_H
