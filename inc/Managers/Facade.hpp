#include "Facade.h"
#include "Scene.h"

void ControlSystem::Facade::initialize()
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    
    ControlSystem::SceneManager::set_scene(scene);
    ControlSystem::SceneManager::set_camera(camera);
}