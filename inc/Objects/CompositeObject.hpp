#include "CompositeObject.h"


CompositeObject::CompositeObject(std::shared_ptr<AbstractObject> &element)
{
    this->elements.push_back(element);
    this->center = element->get_center();
}

CompositeObject::CompositeObject(std::vector<std::shared_ptr<AbstractObject>>& vector)
{
    this->elements = vector;

    this->center.position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (auto &element : this->elements)
    {
        this->center = this->center + element->get_center();
    }

    this->center.position /= this->elements.size();
}

bool CompositeObject::add(const std::shared_ptr<AbstractObject> &element)
{
    this->elements.push_back(element);

    this->center.position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (auto &element : this->elements)
    {
        this->center = this->center + element->get_center();
    }

    this->center.position /= this->elements.size();

    return true;
}

bool CompositeObject::remove(const Iterator &iter)
{
    this->elements.erase(iter);

    this->center.position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (auto &element : this->elements)
    {
        this->center = this->center + element->get_center();
    }

    this->center.position /= this->elements.size();
    return true;
}

bool CompositeObject::IsDrawable()
{
    return false;
}

bool CompositeObject::IsComposite()
{
    return true;
}

Iterator CompositeObject::begin()
{
    return this->elements.begin();
}

Iterator CompositeObject::end()
{
    return this->elements.end();
}

void CompositeObject::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    for (auto &element : this->elements)
    {
        element->accept(visitor);
    }
}
