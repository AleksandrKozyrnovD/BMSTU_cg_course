#include "Window.h"
#include "imgui_impl_sdl2.h"
#include <SDL_render.h>
#include <SDL_video.h>

Window::Window(const Settings& settings)
{
    auto window_flags{static_cast<SDL_WindowFlags>(SDL_WINDOW_ALLOW_HIGHDPI)};
    constexpr int window_center_flag{SDL_WINDOWPOS_CENTERED};

    m_window = SDL_CreateWindow
    (
        settings.title.c_str(),
        window_center_flag,
        window_center_flag,
        settings.width,
        settings.height,
        window_flags
    );

    SDL_RendererFlags renderer_flag
    {
        static_cast<SDL_RendererFlags>(0/*SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED*/)
    };

    m_renderer = SDL_CreateRenderer(m_window, -1, renderer_flag);
    if (m_renderer == nullptr)
    {
        return;
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

SDL_Window* Window::get_native_window() const
{
    return m_window;
}

SDL_Renderer* Window::get_native_renderer() const
{
    return m_renderer;
}