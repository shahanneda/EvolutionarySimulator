//
// Created by Shahan Nedadahandeh on 2022-05-23.
//


#include "GraphicsManager.h"

#include <string>
#include <SDL_opengl.h>
#include <stdexcept>

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

using namespace NeatSquared;

GraphicsManager::GraphicsManager() : networkRenderer() {
    decideGLSLVersion();
    initSDL();
    initImGui();
}

void GraphicsManager::decideGLSLVersion() {
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glslVersion = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
// GL 3.2 Core + GLSL 150
    glslVersion = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    glslVersion = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
}

void GraphicsManager::mainGUILoop() {
    ImGuiIO &io = ImGui::GetIO();
    pollSTL();
    handleInput();
    renderMainFrame(io);
    finishOpenGLRender(io);
}

void GraphicsManager::pollSTL() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            shouldCloseGui = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(window))
            shouldCloseGui = true;
    }
}

void GraphicsManager::finishOpenGLRender(const ImGuiIO &io) const {
    glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

void GraphicsManager::renderMainFrame(const ImGuiIO &io) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));


        ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }
        ImGui::End();


        renderOptions();
        networkRenderer.renderNetwork();
        networkPicker.renderWindow();


    }
    ImGui::Render();
}

void GraphicsManager::renderOptions() {
    ImGui::Begin("Options");
    {
        ImGui::Checkbox("Display Neuron innovation numbers (instead of current values)",
                        &networkRenderer.displayNeuronInnovationNumber);

        ImGui::Checkbox("Display Connection innovation numbers",
                        &networkRenderer.displayConnectionInnovationNumber);

        if (networkRenderer.currentNetwork) {
            std::lock_guard<std::mutex> lock(networkRenderer.currentNetworkMutex);
            for (int inputInnovationNumber: networkRenderer.currentNetwork->inputs) {
                ImGui::InputFloat(("Neuron " + std::to_string(inputInnovationNumber)).c_str(),
                                  &networkRenderer.currentNetwork->getNeuronWithInnovationNumber(
                                          inputInnovationNumber)->currentValue);
            }
        }
    }
    ImGui::End();

}


void GraphicsManager::EmscriptenMainLoop() {
    GraphicsManager::getInstance().mainGUILoop();
}

void GraphicsManager::startMainLoop() {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&GraphicsManager::EmscriptenMainLoop, 0, 1);
#else
    while (!shouldCloseGui) {
        mainGUILoop();
    }
#endif
}

void GraphicsManager::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        throw std::runtime_error("SDL INIT FAILED");
    }
    decideGLSLVersion();

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                                      SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync
}

void GraphicsManager::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Control
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

GraphicsManager::~GraphicsManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void GraphicsManager::handleInput() {
    const float speed = 30.0f;
    if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) {
        networkRenderer.displayOffset = ImVec2(networkRenderer.displayOffset.x - speed,
                                               networkRenderer.displayOffset.y);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) {
        networkRenderer.displayOffset = ImVec2(networkRenderer.displayOffset.x + speed,
                                               networkRenderer.displayOffset.y);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
        networkRenderer.displayOffset = ImVec2(networkRenderer.displayOffset.x,
                                               networkRenderer.displayOffset.y + speed);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
        networkRenderer.displayOffset = ImVec2(networkRenderer.displayOffset.x,
                                               networkRenderer.displayOffset.y - speed);
    }
}

GraphicsManager &GraphicsManager::getInstance() {
    static GraphicsManager instance;
    return instance;
}


