#include "AbstractObject.h"
#include "Application.h"
#include "Buffer.inl"
#include "Camera.h"
#include "Canvas.h"
#include "DrawManager.h"
#include "ImguiInterface.h"
#include "Light.h"
#include "SceneManager.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"
#include "Facade.h"

#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <memory>




Application::Application()
{
    unsigned int init_flags{ SDL_INIT_VIDEO | SDL_INIT_TIMER };

    if (SDL_Init(init_flags) != 0)
    {
        m_exit_status = 1;
    }
    this->m_window = std::make_unique<Window>(Window::Settings{.title="Application"});
}

Application::~Application()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}


int Application::Application::run() {
    if (m_exit_status == 1)
    {
        return m_exit_status;
    }

    Facade::initialize();
    ImguiInterface::init_interface();
    Graphics::SDLCanvas::set_renderer(m_window->get_native_renderer());
    
    float dx, dy;


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_native_window(), m_window->get_native_renderer());
    ImGui_ImplSDLRenderer2_Init(m_window->get_native_renderer());

    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<AbstractObject> camera_obj = nullptr;

    m_running = true;
    // ControlSystem::DrawManager::set_window_size(Buffer::width, Buffer::height);
    ControlSystem::DrawManager::set_window_size(this->m_window->settings.width, this->m_window->settings.height, this->m_window->settings);

    Map map(3);
    ControlSystem::SceneManager::set_map(map);
    ControlSystem::SceneManager::fill_map();
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
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::DrawManager::set_window_size(
                    event.window.data1, event.window.data2, m_window->settings);
                    std::cout << "Resized" << std::endl;
                }
            }
            #include "CodeFragments/InputSDL.hh"
        }

        ImguiInterface::draw_interface();
        ImGui::Render();
    
        // if (ControlSystem::DrawManager::do_we_draw)
        // {
            SDL_SetRenderDrawColor(m_window->get_native_renderer(),0, 0, 0, 255);
            SDL_RenderClear(m_window->get_native_renderer());
        // }
        //Risovanie zdes
        // ControlSystem::DrawManager::draw_scene();
        // ControlSystem::DrawManager::draw_scene_no_lights();
        ControlSystem::DrawManager::new_draw_scene();



        
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), this->m_window->get_native_renderer());
        SDL_RenderPresent(m_window->get_native_renderer());

        //change mouse position to center
        if (this->cursor_controls)
            SDL_WarpMouseInWindow(m_window->get_native_window(), m_window->settings.width / 2, m_window->settings.height / 2);

        //delay for debuggind reasons
        // SDL_Delay(100);
    }

    return m_exit_status;
}

void Application::Application::stop()
{
    m_running = false;
}