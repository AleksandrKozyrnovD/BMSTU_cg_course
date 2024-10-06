#ifndef __LIGHTCASTER_H__
#define __LIGHTCASTER_H__

#include "Drawer.h"

#include "Camera.h"
#include "Light.h"
#include <memory>


class LightCaster : public Drawer
{
public:
    LightCaster() = delete;
    explicit LightCaster(std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light); //lights exactly but camera will do
    ~LightCaster() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;   

protected:
    uint32_t color;
    float diffusion_angle_cos;
    std::shared_ptr<Light>& light_source;

    void process_facet(const Facet& facet) override;
    void process_scanline(float y, GLMSlope& A, GLMSlope& B) override;

    void see_from_viewer();
};

#include "LightCaster.hpp"


#endif
