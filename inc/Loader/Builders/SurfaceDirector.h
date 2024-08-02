#ifndef __SURFACE_DIRECTOR_H__
#define __SURFACE_DIRECTOR_H__

#include "BaseDirector.h"
#include "AbstractSurfaceBuilder.h"

class SurfaceDirector : public BaseDirector
{
public:
    SurfaceDirector() = default;
    explicit SurfaceDirector(std::shared_ptr<AbstractSurfaceBuilder> builder);
    ~SurfaceDirector() = default;

    std::shared_ptr<AbstractObject> create() override;

protected:
    std::shared_ptr<AbstractSurfaceBuilder> builder;
};

#include "SurfaceDirector.hpp"

#endif
