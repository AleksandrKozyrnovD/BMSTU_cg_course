#ifndef __SURFACE_MODEL_H__
#define __SURFACE_MODEL_H__

#include "AbstractSurfaceModel.h"

class SurfaceModel : public AbstractSurfaceModel
{
public:
    SurfaceModel() = default;
    explicit SurfaceModel(const SurfaceModel& other);
    SurfaceModel(SurfaceModel&& other) noexcept;
    explicit SurfaceModel(const std::list<Facet>& surfaces);

    ~SurfaceModel() = default;


    SurfaceModel& operator=(const SurfaceModel& other);
    SurfaceModel& operator=(SurfaceModel&& other) noexcept;

    std::list<Facet>& get_surfaces() override;
    const std::list<Facet>& get_surfaces() const override;

    glm::vec3& get_center() override;
    glm::vec3 get_center() const override;


protected:
    glm::vec3 center;
    std::list<Facet> surfaces;
};

#include "SurfaceModel.hpp"

#endif
