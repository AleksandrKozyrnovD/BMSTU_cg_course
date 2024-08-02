#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Window.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL2/SDL.h>

#include <memory>

#include "ImguiInterface.h"

class Application
{
public:
    Application();
    ~Application();

    int run();
    void stop();

private:
    int m_exit_status{0};
    bool m_running{true};

    std::unique_ptr<Window> m_window{nullptr};
};


#include "Application.hpp"

#endif
