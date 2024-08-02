#include "SurfaceDirector.h"

SurfaceDirector::SurfaceDirector(std::shared_ptr<AbstractSurfaceBuilder> builder)
    : builder(builder)
{}


std::shared_ptr<AbstractObject> SurfaceDirector::create()
{
    this->builder->initialize();

    this->builder->create_facets();
    this->builder->align_facets();

    return this->builder->build();
}
