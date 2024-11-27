#include "Facade.h"

#include "SceneManager.h"

using namespace ControlSystem;


void Facade::initialize()
{
    std::shared_ptr<Scene> scene(new Scene);
    // std::shared_ptr<Camera> camera(new Camera(0, 1.0f, 0));
    std::shared_ptr<Camera> camera(new Camera(
        // {0, 10, 0},
        // {1, 0, 0},
        // {0, -1, 0}

        // 0, 1, 0
        glm::vec3(1.0f, 1.0f, -10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    ));

    SceneManager::set_scene(scene);
    SceneManager::set_camera(camera);
    SceneManager::add_camera(camera);
}