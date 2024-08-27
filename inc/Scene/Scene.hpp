#include "Scene.h"

Scene::Scene()
{
    this->objects = std::list<std::shared_ptr<AbstractObject>>();
    this->cameras = std::list<iterator>();
    this->light_list = std::list<std::shared_ptr<Light>>();
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

std::list<std::shared_ptr<Light>>& Scene::get_lights()
{
    return this->light_list;
}