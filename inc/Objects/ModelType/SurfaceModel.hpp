#include "ModelType/Facet.h"
#include "SurfaceModel.h"


SurfaceModel::SurfaceModel(const SurfaceModel& other)
    : center(other.center), surfaces(other.surfaces)
{}

SurfaceModel::SurfaceModel(SurfaceModel&& other) noexcept
    : center(std::move(other.center)), surfaces(std::move(other.surfaces))
{}

SurfaceModel& SurfaceModel::operator=(const SurfaceModel& other)
{
    center = other.center;
    surfaces = other.surfaces;
    return *this;
}

SurfaceModel::SurfaceModel(const std::list<Facet>& surfaces)
    : surfaces(surfaces)
{
    center.position = { 0.0f, 0.0f, 0.0f, 0.0f };

    for (const Facet& facet : surfaces)
    {
        center.position += facet.get_center().position;
    }

    center.position /= surfaces.size();
}

SurfaceModel& SurfaceModel::operator=(SurfaceModel&& other) noexcept
{
    center = std::move(other.center);
    surfaces = std::move(other.surfaces);
    return *this;
}

std::list<Facet>& SurfaceModel::get_surfaces()
{
    return surfaces;
}

const std::list<Facet>& SurfaceModel::get_surfaces() const
{
    return surfaces;
}

Point& SurfaceModel::get_center()
{
    return center;
}

Point SurfaceModel::get_center() const
{
    return Point(this->center);
}

