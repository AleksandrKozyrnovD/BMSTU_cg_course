#include "AbstractObject.h"
#include "Facade.h"
#include <memory>
// #include "Scene.h"

void ControlSystem::Facade::initialize()
{
    std::shared_ptr<Scene> scene(new Scene);
    std::shared_ptr<Camera> camera(new Camera);

    ControlSystem::SceneManager::set_scene(scene);
    ControlSystem::SceneManager::set_camera(camera);
}