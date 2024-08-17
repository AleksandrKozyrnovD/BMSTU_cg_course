#ifndef __LIGHT_CASTER_H__
#define __LIGHT_CASTER_H__

#include "Drawer.h"
#include "Light.h"

class LightCaster : public Drawer
{
public:
    LightCaster() = delete;
    explicit LightCaster(std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light_source);
    ~LightCaster() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;

protected:
    std::shared_ptr<Light>& light_source;
    uint32_t color;

    virtual void process_scanline(float y, GLMSlope& A, GLMSlope& B) override;
};

#include "LightCaster.hpp"


#endif