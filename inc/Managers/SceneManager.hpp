// #include "AbstractObject.h"
#include "Builders/SurfaceBuilder.h"
#include "Camera.h"
#include "Light.h"
#include "LoadManager.h"
#include "ModelType/Facet.h"
#include "TransformManager.h"
#include "SceneManager.h"
#include <memory>


using namespace ControlSystem;


// std::shared_ptr<Scene> SceneManager::scene = std::shared_ptr<Scene>();
// std::shared_ptr<Camera> SceneManager::camera = std::shared_ptr<Camera>();

std::shared_ptr<Scene> ControlSystem::SceneManager::scene = std::shared_ptr<Scene>();
std::shared_ptr<Camera> ControlSystem::SceneManager::camera = std::shared_ptr<Camera>();
Map ControlSystem::SceneManager::map_of_plots = Map();



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
        if ((*it)->IsDrawable() || (*it)->IsComposite())
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

std::vector<std::shared_ptr<Light>>& SceneManager::get_lights()
{
    return scene->get_lights();
}

void SceneManager::set_scene(std::shared_ptr<Scene> scene)
{
    SceneManager::scene = scene;
}

Map& SceneManager::get_map()
{
    return ControlSystem::SceneManager::map_of_plots;
}

void SceneManager::set_map(Map m)
{
    for (int i = 0; i < map_of_plots.w; ++i)
    {
        for (int j = 0; j < map_of_plots.h; ++j)
        {
            if (map_of_plots.map[i][j].floor != nullptr)
            {
                SceneManager::remove_object(map_of_plots.map[i][j].floor->get_id());
            }
            if (map_of_plots.map[i][j].object != nullptr)
            {
                SceneManager::remove_object(map_of_plots.map[i][j].object->get_id());
            }
        }
    }

    SceneManager::map_of_plots = m;
}

void SceneManager::fill_map()
{
    std::shared_ptr<AbstractObject> floor = nullptr;

    std::shared_ptr<Light> light = std::make_shared<Light>(
        glm::vec3(1.0f, 1.0f, -10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        0
    );
    for (size_t i = 0; i < map_of_plots.w; ++i)
    {
        for (size_t j = 0; j < map_of_plots.h; ++j)
        {
            floor = LoadManager::load_from_file<SurfaceBuilder>("/home/aleksandr/Desktop/bmstu/Curse/CGNEW/model_library/flat.model");
            if (floor != nullptr)
            {
                floor->show = false;
                ControlSystem::TransformManager::move(floor, 1.0f * i, 0.0f, 1.0f * j);
                ControlSystem::SceneManager::add_object(floor);
                map_of_plots.map[i][j].floor = floor;
            }
        }
    }

    ControlSystem::SceneManager::add_light(light);
}


void SceneManager::set_scene_camera(const std::shared_ptr<CameraV2> &camera)
{
    SceneManager::scene->set_camerav2(camera);
}

void SceneManager::set_scene_light(const std::shared_ptr<LightV2> &light)
{
    SceneManager::scene->set_lightv2(light);
}

std::shared_ptr<CameraV2>& SceneManager::get_scene_camera()
{
    return SceneManager::scene->get_camerav2();
}

std::shared_ptr<LightV2>& SceneManager::get_scene_light()
{
    return SceneManager::scene->get_lightv2();
}


std::list<Facet> SceneManager::get_scene_facets()
{
    return SceneManager::scene->get_facets();
}