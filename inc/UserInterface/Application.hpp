#include "AbstractObject.h"
#include "Application.h"
#include "DrawManager.h"
#include "ImguiInterface.h"
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
    this->m_window = std::make_unique<Window>(Window::Settings{"Application"});
}

Application::~Application()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

#include "Builders/SurfaceBuilder.h"

int Application::Application::run() {
    if (m_exit_status == 1)
    {
        return m_exit_status;
    }

    Facade::initialize();
    ImguiInterface::init_interface();
    
    float dx, dy;

    glm::vec3 center = glm::vec3(0, 0, -2);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 forward = glm::vec3(0, 0, 1);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(center, up, forward);
    std::shared_ptr<Light> light = std::make_shared<Light>(center + glm::vec3(0.0f, 0.0f, 0.0f), up, forward, 0xff000000);



    std::shared_ptr<AbstractObject> obj2 = std::static_pointer_cast<AbstractObject>(camera);
    std::shared_ptr<AbstractObject> obj4 = std::static_pointer_cast<AbstractObject>(light);

    
    DrawVisitor visitor(camera);


    std::shared_ptr<AbstractObject> obj =
    ControlSystem::LoadManager::load_from_file<SurfaceBuilder>("/home/aleksandr/Desktop/bmstu/Curse/CGNEW/models/test.txt");


    std::shared_ptr<AbstractObject> obj3 =
    ControlSystem::LoadManager::load_from_file<SurfaceBuilder>("/home/aleksandr/Desktop/bmstu/Curse/CGNEW/models/test1.txt");


    Graphics::SDLCanvas::set_renderer(m_window->get_native_renderer());


    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    ControlSystem::SceneManager::set_scene(scene);

    ControlSystem::SceneManager::set_camera(camera);
    ControlSystem::SceneManager::add_light(light);
    ControlSystem::SceneManager::add_object(obj3);
    ControlSystem::SceneManager::add_object(obj);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_native_window(), m_window->get_native_renderer());
    ImGui_ImplSDLRenderer2_Init(m_window->get_native_renderer());

    // std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<AbstractObject> camera_obj = nullptr;

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
            #include "CodeFragments/InputSDL.hh"
        }

        ImguiInterface::draw_interface();
        ImGui::Render();
    

        SDL_SetRenderDrawColor(m_window->get_native_renderer(),0, 0, 0, 255);
        SDL_RenderClear(m_window->get_native_renderer());
        //Risovanie zdes
        // ControlSystem::TransformManager::rotate(obj, 1.0f, 1.0f, 1.0f);
        // ControlSystem::TransformManager::rotate(obj2, 0.0f, 1.0f, 0.0f);
        ControlSystem::DrawManager::draw_scene();


        
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