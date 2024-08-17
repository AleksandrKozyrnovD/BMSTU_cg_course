#include "LightCaster.h"

#include <glm/geometric.hpp>

#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"
#include "glm/ext/matrix_transform.hpp"


LightCaster::LightCaster(std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light)
    : Drawer(camera), light_source(light)
{}

void LightCaster::process_scanline(float y, GLMSlope& A, GLMSlope& B)
{
    glm::vec3 p0 = A.get();
    glm::vec3 p1 = B.get();


    int x0 = p0.x;
    int x1 = p1.x;

    if (x0 > x1) std::swap(x0, x1);

    //for future me to fix
    if (y < 0) y = 0;
    if (y > 720) y = 719;
    if (x0 < 0) x0 = 0;
    if (x1 > 1280) x1 = 1279;

    for (; x0 < x1; ++x0)
    {
        if (ControlSystem::Buffer::depth_buffer[y][x0] >= p0.z && p0.z > 0.1f) //facet is not behind camera so > 0.1f
        {
            //loss of some intensity by traveling distance of p0.z so divide by p0.z + const
            //RGBA8888
            uint8_t red = (this->color & 0xFF) / (p0.z + 0.1f);
            uint8_t green = ((this->color >> 8) & 0xFF) / (p0.z + 0.1f);
            uint8_t blue = ((this->color >> 16) & 0xFF) / (p0.z + 0.1f);
            uint8_t alpha = ((this->color >> 24) & 0xFF);
            uint32_t newcolor = (red << 24) | (green << 16) | (blue << 8) | alpha;
            ControlSystem::Buffer::frame_buffer[y][x0] = newcolor;
        }
    }

    A.advance();
    B.advance();
}


void LightCaster::visit(Model& obj)
{
    //calculating transform matrix from light source to camera view
    glm::vec3 translation = this->light_source->get_center()
                          - this->camera->get_center();

    glm::vec3 axis = glm::cross(this->camera->forward, this->light_source->forward);
    float angle = glm::acos(glm::dot(this->camera->forward,this->light_source->forward));
    glm::mat4x4 rotation = glm::rotate(glm::mat4x4(1.0f), angle, axis);
    rotation = glm::translate(rotation, translation);

    this->transform = obj.transform * rotation;
    // this->transform = obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->process_facet(facet);
    }
}


void LightCaster::visit(Camera& obj)
{
    return;
}


void LightCaster::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<LightCaster>(*this));
}

void LightCaster::visit(Light& obj)
{
    return;
}