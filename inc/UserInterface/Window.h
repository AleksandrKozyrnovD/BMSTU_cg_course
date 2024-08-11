#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL2/SDL.h>

#include <string>

class Window
{
public:
    struct Settings
    {
        std::string title;
        int width{1280};
        int height{720};
    };

  explicit Window(const Settings& settings);
  ~Window();

  [[nodiscard]] SDL_Window* get_native_window() const;
  [[nodiscard]] SDL_Renderer* get_native_renderer() const;

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
};

#include "Window.hpp"

#endif

