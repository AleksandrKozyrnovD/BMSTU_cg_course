#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "BaseManager.h"
#include "Camera.h"
#include "Light.h"
#include "ModelType/Facet.h"
#include "Scene.h"
#include "Map/Map.h"
#include <memory>

namespace ControlSystem
{
    class SceneManager : public BaseManager
    {
    public:
        SceneManager() = delete;
        // explicit SceneManager(std::shared_ptr<Scene> scene);
        ~SceneManager() = default;

        static void add_camera(std::shared_ptr<AbstractObject> camera);
        static void set_scene(std::shared_ptr<Scene> scene);
        static std::shared_ptr<Scene> get_scene();

        static void set_camera(std::shared_ptr<Camera> camera);

        static void add_object(std::shared_ptr<AbstractObject> object);
        static std::vector<std::shared_ptr<AbstractObject>> get_drawable_objects();
        static std::vector<std::shared_ptr<AbstractObject>> get_objects();
        static std::shared_ptr<AbstractObject> get_object(std::size_t id);
        static std::vector<std::size_t> get_object_ids();
        static void remove_object(std::size_t id);

        static std::vector<std::shared_ptr<AbstractObject>> get_cameras();
        static std::vector<std::size_t> get_camera_ids();
        static std::shared_ptr<Camera> get_camera(std::size_t id);
        static std::shared_ptr<Camera> get_main_camera();
        static void remove_camera(std::size_t id);
        static void set_camera(std::size_t id);

        static void clear_scene();

        static void add_light(std::shared_ptr<Light> light);
        static void remove_light(std::size_t id);
        static std::vector<std::shared_ptr<Light>>& get_lights();

        static Map& get_map();
        static void set_map(Map map);
        static void fill_map();

        static size_t get_map_size()
        {
            return SceneManager::scene->mapsize;
        }


        static std::shared_ptr<CameraV2>& get_scene_camera();
        static std::shared_ptr<LightV2>& get_scene_light();

        static void set_scene_camera(const std::shared_ptr<CameraV2>& camera);
        static void set_scene_light(const std::shared_ptr<LightV2>& light);

        static std::list<Facet> get_scene_facets();

        static std::string load_file;

        // static void save_scene();

    protected:
        static std::shared_ptr<Scene> scene;
        static std::shared_ptr<Camera> camera;
        static Map map_of_plots;
    };
}

#include "SceneManager.hpp"

#endif
