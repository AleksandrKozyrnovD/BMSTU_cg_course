#include "Application.h"
#include "Canvas.h"
#include "ImguiInterface.h"
#include "SceneManager.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL_events.h>
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


#include "Camera.h"
#include "AbstractObject.h"
#include "DrawManager.h"
#include "LoadManager.h"
#include "Builders/SurfaceBuilder.h"
#include "TransformManager.h"
#include "Light.h"


int Application::Application::run() {
    if (m_exit_status == 1)
    {
        return m_exit_status;
    }

    float dx, dy;

    glm::vec3 center = glm::vec3(0, 0, -2);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 forward = glm::vec3(0, 0, -1);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(center, up, forward);

    std::shared_ptr<AbstractObject> obj2 = std::static_pointer_cast<AbstractObject>(camera);
    
    DrawVisitor visitor(camera);

    std::shared_ptr<AbstractObject> obj =
    ControlSystem::LoadManager::load_from_file<SurfaceBuilder>("/home/aleksandr/Desktop/bmstu/Curse/CGNEW/models/test.txt");

    Graphics::SDLCanvas::set_renderer(m_window->get_native_renderer());


    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    ControlSystem::SceneManager::set_scene(scene);

    ControlSystem::SceneManager::set_camera(camera);
    ControlSystem::SceneManager::add_object(obj);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ImGui::GetIO()};

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // SDL_SetWindowInputFocus(this->m_window->get_native_window());
    SDL_RaiseWindow(m_window->get_native_window());

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
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_W)
                    {
                        glm::vec3 v = camera->forward * 1.0f;
                        ControlSystem::TransformManager::move(obj2, v.x, v.y, v.z);
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                    {
                        glm::vec3 v = camera->forward * 1.0f;
                        ControlSystem::TransformManager::move(obj2, -v.x, -v.y, -v.z);
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_A)
                    {
                        glm::vec3 v = camera->right * 1.0f;
                        ControlSystem::TransformManager::move(obj2, -v.x, -v.y, -v.z);
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                    {
                        glm::vec3 v = camera->right * 1.0f;
                        ControlSystem::TransformManager::move(obj2, v.x, v.y, v.z);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    dx = event.motion.xrel;
                    dy = event.motion.yrel;
                    ControlSystem::TransformManager::rotate(obj2, dy / 10.0f,-dx / 10.0f, 0.0f);
                    break;

                default:
                    break;
            }
        }

        ImguiInterface::draw_interface();
        ImGui::Render();
    

        SDL_SetRenderDrawColor(m_window->get_native_renderer(),0, 0, 0, 255);
        SDL_RenderClear(m_window->get_native_renderer());
        //Risovanie zdes
        obj->accept(std::make_shared<DrawVisitor>(visitor));

        ControlSystem::TransformManager::rotate(obj, 0.1, 0.1, 0.1);
        ControlSystem::DrawManager::draw_scene_no_lights();

        
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), this->m_window->get_native_renderer());
        SDL_RenderPresent(m_window->get_native_renderer());

        //delay for debuggind reasons
        // SDL_Delay(100);
    }

    return m_exit_status;
}

void Application::Application::stop()
{
    m_running = false;
}