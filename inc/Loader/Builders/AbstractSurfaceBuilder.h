#ifndef __BASE_ABSTRACT_SURFACE_BUILDER_H__
#define __BASE_ABSTRACT_SURFACE_BUILDER_H__

#include "../../Objects/Model.h"
#include "ModelType/AbstractSurfaceModel.h"

class AbstractSurfaceBuilder
{
public:
    AbstractSurfaceBuilder() = default;
    virtual ~AbstractSurfaceBuilder() = default;

    virtual void initialize() = 0;
    virtual std::shared_ptr<Model> build() = 0;

    virtual bool create_facets() = 0;
    virtual bool align_facets() = 0;

protected:
    std::shared_ptr<AbstractSurfaceModel> implementation { nullptr };
};



#endif
