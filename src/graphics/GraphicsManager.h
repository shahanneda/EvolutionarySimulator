//
// Created by Shahan Nedadahandeh on 2022-05-23.
//

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace NeatSquared {

/*
 * GraphicsManager is completely responsible for all aspects of the rendering and GUI
 * In order for GraphicsManager to work well on with webassembly (emscripten compiler), it must pass a function pointer to a c style library, which is why this class is a singleton, to allow for an easy way
 * to make a static main loop function that can be passed to the c api.
 */
    class GraphicsManager {
    private:
        char *glslVersion;
        SDL_Window *window;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        bool shouldCloseGui = false;
        SDL_GLContext glContext;

        GraphicsManager();

        ~GraphicsManager();

    public:
        void startMainLoop();

        static GraphicsManager &getInstance();

        // Because this class should not be instantiated from the outside, instead use getInstance
        GraphicsManager(GraphicsManager const &) = delete;

        void operator=(GraphicsManager const &) = delete;

    private:
        void decideGLSLVersion();

        void initSDL();

        void initImGui();

        void mainGUILoop();


        void finishOpenGLRender(const ImGuiIO &io) const;

        void renderMainFrame(const ImGuiIO &io);

        void pollSTL();

        static void EmscriptenMainLoop();
    };
}
#endif //GRAPHICSMANAGER_H
