#ifndef __ABSTRACT_OBJECT_H__
#define __ABSTRACT_OBJECT_H__

#include <memory>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "AbstractVisitor.h"



class AbstractObject;
using Iterator = std::vector<std::shared_ptr<AbstractObject>>::iterator;

class AbstractObject
{
public:
    AbstractObject() { this->id = nextid++; };
    virtual ~AbstractObject() = default;

    virtual bool IsDrawable()  { return false; }
    virtual bool IsComposite() { return false; }

    virtual bool add(const std::shared_ptr<AbstractObject>& obj) { return false; }
    virtual bool remove(const Iterator& iterator) { return false; }

    virtual Iterator begin() { return Iterator(); }
    virtual Iterator end()   {return Iterator(); }

    virtual void accept(std::shared_ptr<AbstractVisitor> visitor) = 0;

    size_t get_id() { return this->id; }

    glm::vec3 get_center() const { return glm::vec3(this->center); }
    glm::vec3& get_center() { return this->center; }

protected:
    std::size_t id;
    static std::size_t nextid;
    glm::vec3 center;
    glm::mat4x4 transform = glm::mat4x4(1.0f);
};

#include "AbstractObject.hpp"


#endif