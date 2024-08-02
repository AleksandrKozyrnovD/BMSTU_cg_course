#include "Application.h"
#include "ImguiInterface.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL_render.h>
#include <SDL_timer.h>


Application::Application()
{
    unsigned int init_flags{ SDL_INIT_VIDEO | SDL_INIT_TIMER };

    if (SDL_Init(init_flags) != 0)
    {
        m_exit_status = 1;
    }
    this->m_window = std::make_unique<Window>(Window::Settings{"Application"});
}

Application::~Application()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

// void drawline(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
// {
//     SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);

//     int x = x1;
//     int y = y1;
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);
//     int sx = x2 > x1 ? 1 : -1;
//     int sy = y2 > y1 ? 1 : -1;
//     bool swap = false;
//     if (dy > dx)
//     {
//         swap = true;
//         int t = dx;
//         dx = dy;
//         dy = t;
//     }

//     int dy2 = 2 * dy;
//     int dx2 = 2 * dx;
//     int error = dy2 - dx;

//     for (int i = 0; i < dx; i++)
//     {
//         SDL_RenderDrawPoint(renderer, x, y);
//         while (error >= 0)
//         {
//             if (!swap)
//             {
//                 y += sy;
//             }
//             else
//             {
//                 x += sx;
//             }
//             error -= dx2;
//         }
//         if (!swap)
//         {
//             x += sx;
//         }
//         else
//         {
//             y += sy;
//         }
//         error += dy2;
//     }

//     // SDL_RenderPresent(renderer);

//     return;
// }

int Application::Application::run() {
    if (m_exit_status == 1)
    {
        return m_exit_status;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_native_window(), m_window->get_native_renderer());
    ImGui_ImplSDLRenderer2_Init(m_window->get_native_renderer());

    m_running = true;
    while (m_running)
    {
        SDL_Event event{};
        while (SDL_PollEvent(&event) == 1)
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                this->stop();
            }
        }

        ImguiInterface::draw_interface();
        ImGui::Render();
    

        SDL_SetRenderDrawColor(m_window->get_native_renderer(),100, 100, 100, 255);
        SDL_RenderClear(m_window->get_native_renderer());
        //Risovanie zdes
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), this->m_window->get_native_renderer());
        SDL_RenderPresent(m_window->get_native_renderer());
    }

    return m_exit_status;
}

void Application::Application::stop()
{
    m_running = false;
}