#include "SceneManager.h"

using namespace ControlSystem;


std::shared_ptr<Scene> SceneManager::scene = std::shared_ptr<Scene>();
std::shared_ptr<Camera> SceneManager::camera = std::shared_ptr<Camera>();

std::shared_ptr<Scene> SceneManager::get_scene()
{
    return scene;
}

void SceneManager::set_camera(std::shared_ptr<Camera> new_camera)
{
    camera = new_camera;
}

void SceneManager::add_object(std::shared_ptr<AbstractObject> object)
{
    scene->add_object(object);
}

std::vector<std::shared_ptr<AbstractObject>> SceneManager::get_drawable_objects()
{
    std::vector<std::shared_ptr<AbstractObject>> objects;
    for (auto it = scene->begin(); it != scene->end(); ++it)
    {
        if ((*it)->IsDrawable())
        {
            objects.push_back(*it);
        }
    }
    return objects;
}


std::vector<std::shared_ptr<AbstractObject>> SceneManager::get_objects()
{
    std::vector<std::shared_ptr<AbstractObject>> objects;
    for (auto it = scene->begin(); it != scene->end(); ++it)
    {
        objects.push_back(*it);
    }
    return objects;
}


void SceneManager::add_camera(std::shared_ptr<AbstractObject> camera)
{
    scene->add_camera(camera);
}

std::shared_ptr<AbstractObject> SceneManager::get_object(std::size_t id)
{
    std::shared_ptr<AbstractObject> obj = nullptr;
    for (auto it = scene->begin(); obj == nullptr && it != scene->end(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            obj = *it;
        }
    }
    return obj;
}

void SceneManager::remove_object(std::size_t id)
{
    for (auto it = scene->cbegin(); it!= scene->cend(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            scene->remove_object(it);
            return;
        }
    }
}

std::vector<std::shared_ptr<AbstractObject>> SceneManager::get_cameras()
{
    std::vector<std::shared_ptr<AbstractObject>> cameras;
    for (auto it = scene->beginCamera(); it!= scene->endCamera(); ++it)
    {
        cameras.push_back(**it);
    }
    return cameras;
}

std::shared_ptr<Camera> SceneManager::get_camera(std::size_t id)
{
    for (auto it = scene->beginCamera(); it!= scene->endCamera(); ++it)
    {
        if ((**it)->get_id() == id)
        {
            auto obj = std::dynamic_pointer_cast<Camera>(**it);
            if (obj == nullptr)
            {
                throw std::runtime_error("Object is not a camera");
            }
            return obj;
        }
    }
    return nullptr;
}


void SceneManager::remove_camera(std::size_t id)
{
    for (auto it = scene->beginCamera(); it!= scene->endCamera(); ++it)
    {
        if ((**it)->get_id() == id)
        {
            scene->remove_camera(it);
            return;
        }
    }
}

void SceneManager::set_camera(std::size_t id)
{
    camera = get_camera(id);
}

void SceneManager::clear_scene()
{
    scene->cameras.clear();
    scene->objects.clear();
    scene->light_list.clear();
}

std::shared_ptr<Camera> SceneManager::get_main_camera()
{
    return camera;
}

std::vector<std::size_t> SceneManager::get_object_ids()
{
    std::vector<std::size_t> ids;
    for (auto it = scene->begin(); it!= scene->end(); ++it)
    {
        ids.push_back((*it)->get_id());
    }
    return ids;
}

std::vector<std::size_t> SceneManager::get_camera_ids()
{
    std::vector<std::size_t> ids;
    for (auto it = scene->beginCamera(); it!= scene->endCamera(); ++it)
    {
        ids.push_back((**it)->get_id());
    }
    return ids;
}

void SceneManager::add_light(std::shared_ptr<Light> light)
{
    scene->add_light(light);
}

void SceneManager::remove_light(std::size_t id)
{
    scene->remove_light(id);
}

std::list<std::shared_ptr<Light>>& SceneManager::get_lights()
{
    return scene->get_lights();
}


// void SceneManager::make_composite(std::vector<size_t> ids)
// {
//     std::vector<std::shared_ptr<AbstractObject>> objects;
//     for (auto it = ids.begin(); it!= ids.end(); ++it) {
//         objects.push_back(get_object(*it));
//     }
//     scene->add_composite(objects);
// }


// std::shared_ptr<Scene> SceneManager::get_scene()
// {
//     return scene;
// }

void SceneManager::set_scene(std::shared_ptr<Scene> scene)
{
    SceneManager::scene = scene;
}

// std::shared_ptr<Camera>& SceneManager::get_camera()
// {
//     return camera;
// }

// void SceneManager::set_camera(std::shared_ptr<Camera> camera)
// {
//     camera = camera;
// }

// void SceneManager::set_camera(int id)
// {
//     std::shared_ptr<Camera> obj = get_scene()->get_cameras().at(id);
//     set_camera(obj);
// }

// void SceneManager::add_camera(std::shared_ptr<Camera> camera)
// {
//     scene->add_camera(camera);
// }

// void SceneManager::add_object(std::shared_ptr<AbstractObject>& object)
// {
//     scene->add_model(object);
// }

// std::vector<std::shared_ptr<AbstractObject>>& SceneManager::get_objects()
// {
//     return scene->get_models();
// }

// void SceneManager::remove_object(int id)
// {
//     scene->remove_model(id);
// }

// void SceneManager::remove_camera(int id)
// {
//     scene->remove_camera(id);
// }

// std::shared_ptr<AbstractObject> SceneManager::get_object(int id)
// {
//     return scene->get_object(id);
// }