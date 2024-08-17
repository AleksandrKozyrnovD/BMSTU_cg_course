#include "DrawVisitor.h"

#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"


DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : Drawer(camera)
{}

#include <iostream>
void DrawVisitor::process_scanline(float y, GLMSlope& A, GLMSlope& B)
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
        //check if pixel inside viewframe. 1280x720

        if (ControlSystem::Buffer::depth_buffer[y][x0] > p0.z && p0.z > 0.1f) //facet is not behind camera so > 0.1f
        {
            // std::cout << "new z value: " << p0.z << " for (x,y): (" << x0 << "," << y << "), and color: " << color <<std::endl;

            //RGBA8888
            // uint8_t red = (this->color & 0xFF);
            // uint8_t green = ((this->color << 8) & 0xFF);
            // uint8_t blue = ((this->color << 16) & 0xFF);
            // uint8_t alpha = ((this->color << 24) & 0xFF);
            // std::cout << "Red: " << red << " Green: " << green << " Blue: " << blue << " Alpha: " << alpha << std::endl;

            ControlSystem::Buffer::frame_buffer[y][x0] = this->color;
            ControlSystem::Buffer::depth_buffer[y][x0] = p0.z;
        }
    }

    A.advance();
    B.advance();
}


void DrawVisitor::visit(Model& obj)
{
    this->transform = obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->color = facet.color;
        this->process_facet(facet);
    }
}


void DrawVisitor::visit(Camera& obj)
{
    return;
}


void DrawVisitor::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<DrawVisitor>(*this));
}

void DrawVisitor::visit(Light& obj)
{
    return;
}