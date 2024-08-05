#ifndef __ABSTRACT_SURFACE_MODEL_H__
#define __ABSTRACT_SURFACE_MODEL_H__

#include <list>

#include "Facet.h"


class AbstractSurfaceModel
{
public:
    AbstractSurfaceModel() = default;
    virtual ~AbstractSurfaceModel() = default;

    virtual std::list<Facet>& get_surfaces() = 0;
    virtual const std::list<Facet>& get_surfaces() const = 0;

    virtual glm::vec3& get_center() = 0;
    virtual glm::vec3 get_center() const = 0;
};

#endif