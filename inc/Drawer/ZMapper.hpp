#include "ZMapper.h"


#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"


ZMapper::ZMapper(std::shared_ptr<Camera>& camera)
    : Drawer(camera)
{}

void ZMapper::process_scanline(float y, GLMSlope& A, GLMSlope& B)
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
        if (ControlSystem::Buffer::depth_buffer[y][x0] > p0.z && p0.z > 0.1f) //facet is not behind camera so > 0.1f
        {
            ControlSystem::Buffer::depth_buffer[y][x0] = p0.z;
        }
    }

    A.advance();
    B.advance();
}


void ZMapper::visit(Model& obj)
{
    this->transform = obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->process_facet(facet);
    }
}


void ZMapper::visit(Camera& obj)
{
    return;
}


void ZMapper::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<ZMapper>(*this));
}

void ZMapper::visit(Light& obj)
{
    return;
}