#include "Loader/Readers/AbstractFacetReader.h"
#include "ModelType/SurfaceModel.h"
#include "SurfaceBuilder.h"
#include <memory>

SurfaceBuilder::SurfaceBuilder(std::shared_ptr<AbstractFacetReader> reader)
    : reader(reader)
{}


void SurfaceBuilder::initialize()
{
    return;
}

bool SurfaceBuilder::create_facets()
{
    size_t count = this->reader->get_count();

    bool error = false;
    for (size_t i = 0; !error && i < count; ++i)
    {
        Facet facet = this->reader->read_facet();
        this->facets.push_back(facet);
    }

    if (!error)
    {
        this->implementation = std::make_shared<SurfaceModel>(this->facets);
    }
    return !error;
}


bool SurfaceBuilder::align_facets()
{
    glm::vec3 center = this->implementation->get_center();
    auto facets = this->implementation->get_surfaces();

    for (auto &facet : facets)
    {
        facet.fix_direction(center);
    }

    return true;
}

std::shared_ptr<Model> SurfaceBuilder::build()
{
    return std::make_shared<Model>(this->implementation);
}
