#ifndef __SCENE_H__
#define __SCENE_H__

#include "AbstractObject.h"
#include "Camera.h"
#include "Light.h"
#include "ModelType/Facet.h"
// #include "SceneManager.h"

#include <list>

namespace ControlSystem
{
    class SceneManager;
}

class Scene
{
    using iterator = std::list<std::shared_ptr<AbstractObject>>::iterator;
    using const_iterator = std::list<std::shared_ptr<AbstractObject>>::const_iterator;
    using reverse_iterator = std::list<std::shared_ptr<AbstractObject>>::reverse_iterator;
    using const_reverse_iterator = std::list<std::shared_ptr<AbstractObject>>::const_reverse_iterator;
    using size_type = std::list<std::shared_ptr<AbstractObject>>::size_type;
    using difference_type = std::list<std::shared_ptr<AbstractObject>>::difference_type;
    using iteratorCamera = std::list<iterator>::const_iterator;
    friend class ControlSystem::SceneManager;
public:
    Scene();
    ~Scene() = default;
    void add_object(const std::shared_ptr<AbstractObject> obj);
    void remove_object(const const_iterator& it);
    // void add_composite(const std::vector<std::shared_ptr<AbstractObject>> Objects);

    void add_camera(const std::shared_ptr<AbstractObject> obj);
    void remove_camera(const std::list<iterator>::const_iterator &it);
    std::shared_ptr<AbstractObject> get_camera(const iteratorCamera &it);


    void add_light(const std::shared_ptr<Light> obj);
    void remove_light(const size_t id);
    std::vector<std::shared_ptr<Light>>& get_lights();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    size_type size() const;

    iteratorCamera beginCamera();
    iteratorCamera endCamera();

    void set_camerav2(const std::shared_ptr<CameraV2>& cam);
    std::shared_ptr<CameraV2>& get_camerav2();

    void set_lightv2(const std::shared_ptr<LightV2>& light);
    std::shared_ptr<LightV2>& get_lightv2();

    std::list<Facet> get_facets();

protected:
    std::list<std::shared_ptr<AbstractObject>> objects;
    std::list<iterator> cameras;
    std::vector<std::shared_ptr<Light>> light_list;

    std::shared_ptr<CameraV2> cam2;
    std::shared_ptr<LightV2> light2;
};

#include "Scene.hpp"

#endif // SCENE_H