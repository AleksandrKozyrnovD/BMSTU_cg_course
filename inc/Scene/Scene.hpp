#include "Camera.h"
#include "ModelType/Facet.h"
#include "Scene.h"
#include <memory>

Scene::Scene()
{
    this->objects = std::list<std::shared_ptr<AbstractObject>>();
    this->cameras = std::list<iterator>();
    this->light_list = std::vector<std::shared_ptr<Light>>();
}


void Scene::add_object(const std::shared_ptr<AbstractObject> obj)
{
    this->objects.push_back(obj);
}
void Scene::remove_object(const const_iterator& it)
{
    this->objects.erase(it);
}

void Scene::add_camera(const std::shared_ptr<AbstractObject> obj)
{
    this->objects.push_back(obj);
    auto it = this->objects.begin();
    auto itnext = ++this->objects.begin();

    for (; itnext != this->objects.end(); ++it, ++itnext);

    this->cameras.push_back(it);
}

void Scene::remove_camera(const std::list<iterator>::const_iterator &it)
{
    this->objects.erase(*it);
    this->cameras.erase(it);
}

std::shared_ptr<AbstractObject> Scene::get_camera(const iteratorCamera &it)
{
    return **it;
}

Scene::iterator Scene::begin()
{
    return this->objects.begin();
}

Scene::iterator Scene::end()
{
    return this->objects.end();
}

Scene::const_iterator Scene::begin() const
{
    return this->objects.begin();
}

Scene::const_iterator Scene::end() const
{
    return this->objects.end();
}

Scene::const_iterator Scene::cbegin() const
{
    return this->objects.cbegin();
}

Scene::const_iterator Scene::cend() const
{
    return this->objects.cend();
}

Scene::reverse_iterator Scene::rbegin()
{
    return this->objects.rbegin();
}

Scene::reverse_iterator Scene::rend()
{
    return this->objects.rend();
}

Scene::const_reverse_iterator Scene::rbegin() const
{
    return this->objects.rbegin();
}

Scene::const_reverse_iterator Scene::rend() const
{
    return this->objects.rend();
}

Scene::const_reverse_iterator Scene::crbegin() const
{
    return this->objects.crbegin();
}

Scene::const_reverse_iterator Scene::crend() const
{
    return this->objects.crend();
}

Scene::size_type Scene::size() const
{
    return this->objects.size();
}

Scene::iteratorCamera Scene::beginCamera() {
    return this->cameras.cbegin();
}

Scene::iteratorCamera Scene::endCamera() {
    return this->cameras.cend();
}

void Scene::add_light(const std::shared_ptr<Light> obj)
{
    this->light_list.push_back(obj);
    this->objects.push_back(obj);
}

void Scene::remove_light(const size_t id)
{
    bool not_found = true;
    for (auto it = this->light_list.begin(); not_found && it != this->light_list.end(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            this->light_list.erase(it);
            not_found = false;
        }
    }
}

std::vector<std::shared_ptr<Light>>& Scene::get_lights()
{
    return this->light_list;
}


void Scene::set_camerav2(const std::shared_ptr<CameraV2>& camera)
{
    this->cam2 = camera;
}

std::shared_ptr<CameraV2>& Scene::get_camerav2()
{
    return this->cam2;
}

void Scene::set_lightv2(const std::shared_ptr<LightV2>& light)
{
    this->light2 = light;
}

std::shared_ptr<LightV2>& Scene::get_lightv2()
{
    return this->light2;
}


std::list<Facet> Scene::get_facets()
{
    std::list<Facet> facets;
    std::shared_ptr<Model> m;
    for (auto& obj : this->objects)
    {
        if (obj->IsDrawable())
        {
            m = std::dynamic_pointer_cast<Model>(obj);
            if (m != nullptr)
            {
                for (auto& facet : m->model->get_surfaces())
                {
                    facets.push_back(facet);
                }
            }
        }
    }

    return facets;
}