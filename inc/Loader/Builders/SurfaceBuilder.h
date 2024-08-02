#ifndef __SURFACE_BUILDER_H__
#define __SURFACE_BUILDER_H__

#include "AbstractSurfaceBuilder.h"
#include "../Readers/AbstractFacetReader.h"


class SurfaceBuilder : public AbstractSurfaceBuilder
{
public: 
    SurfaceBuilder() = default;
    explicit SurfaceBuilder(std::shared_ptr<AbstractFacetReader> reader);
    ~SurfaceBuilder() = default;

    void initialize() override;
    std::shared_ptr<Model> build() override;

    bool create_facets() override;
    bool align_facets() override;

protected:
    std::shared_ptr<AbstractFacetReader> reader;
    std::list<Facet> facets;
};

#include "SurfaceBuilder.hpp"

#endif
