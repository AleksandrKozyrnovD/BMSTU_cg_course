#include "Transform.h"
#include "SceneManager.h"


Actions::Scene::AddObject::AddObject(std::shared_ptr<AbstractObject>& object)
    : obj(object)
{
    this->method = &ControlSystem::SceneManager::add_object;
}

void Actions::Scene::AddObject::Execute()
{
    (*method)(obj);
}

Actions::Scene::RemoveObject::RemoveObject(size_t id)
    : id(id)
{
    this->method = &ControlSystem::SceneManager::remove_object;
}

void Actions::Scene::RemoveObject::Execute()
{
    (*method)(id);
}

Actions::Scene::GetObject::GetObject(std::shared_ptr<AbstractObject>& object, size_t id)
    : obj(object), id(id)
{
    this->method = &ControlSystem::SceneManager::get_object;
}

void Actions::Scene::GetObject::Execute()
{
    this->obj = (*method)(id);
}

Actions::Scene::GetObjects::GetObjects(std::shared_ptr<AbstractObject>& object)
    : obj(object)
{
    this->method = &ControlSystem::SceneManager::get_objects;
}

void Actions::Scene::GetObjects::Execute()
{
    std::vector<std::shared_ptr<AbstractObject>> objects = (*method)();
    this->obj = std::make_shared<CompositeObject>(objects);
}

Actions::Scene::ClearScene::ClearScene()
{
    this->method = &ControlSystem::SceneManager::clear_scene;
}

void Actions::Scene::ClearScene::Execute()
{
    (*method)();
}

Actions::Scene::AddCamera::AddCamera(std::shared_ptr<AbstractObject>& camera)
    : obj(camera)
{
    this->method = &ControlSystem::SceneManager::add_camera;
}

void Actions::Scene::AddCamera::Execute()
{
    (*method)(obj);
}

Actions::Scene::RemoveCamera::RemoveCamera(size_t id)
    : id(id)
{
    this->method = &ControlSystem::SceneManager::remove_camera;
}

void Actions::Scene::RemoveCamera::Execute()
{
    (*method)(id);
}

Actions::Scene::SetMainCamera::SetMainCamera(size_t id)
    : id(id)
{
    this->method = &ControlSystem::SceneManager::set_camera;
}

void Actions::Scene::SetMainCamera::Execute()
{
    (*method)(id);
}

Actions::Scene::GetMainCamera::GetMainCamera(std::shared_ptr<Camera>& camera, size_t id)
    : obj(camera), id(id)
{
    this->method = &ControlSystem::SceneManager::get_camera;
}

void Actions::Scene::GetMainCamera::Execute()
{
    this->obj = (*method)(id);
}