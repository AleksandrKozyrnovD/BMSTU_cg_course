#include "DrawVisitor.h"

#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"


DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : Drawer(camera)
{}

void DrawVisitor::process_facet(const Facet& facet)
{
    /*
    https://bisqwit.iki.fi/jutut/kuvat/programming_examples/polytut/ <---- tutorial and prime example from where i got code
    */

    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    glm::vec3 p0 = facet.A;
    glm::vec3 p1 = facet.B;
    glm::vec3 p2 = facet.C;

    //apply model
    p0 = glm::vec3(model * glm::vec4(p0, 1.0f));
    p1 = glm::vec3(model * glm::vec4(p1, 1.0f));
    p2 = glm::vec3(model * glm::vec4(p2, 1.0f));

    //apply view
    p0 = glm::vec3(view * glm::vec4(p0, 1.0f));
    p1 = glm::vec3(view * glm::vec4(p1, 1.0f));
    p2 = glm::vec3(view * glm::vec4(p2, 1.0f));

    //remember old z
    // float z0 = p0.z;
    // float z1 = p1.z;
    // float z2 = p2.z;

    //project
    p0 = glm::vec3(glm::project(p0, glm::mat4x4(1.0f), projection, viewport));
    p1 = glm::vec3(glm::project(p1, glm::mat4x4(1.0f), projection, viewport));
    p2 = glm::vec3(glm::project(p2, glm::mat4x4(1.0f), projection, viewport));


    // //apply z
    // p0.z = z0;
    // p1.z = z1;
    // p2.z = z2;

    // Sort the points in order of Y coordinate, so first point is the top one.
    // In case of equal Y coordinates, sort according to X coordinates.
    // Using a 3-input sorting network.
    if (p0.y > p1.y)
    {
        std::swap(p0, p1);
    }
    if (p0.y > p2.y)
    {
        std::swap(p0, p2);
    }
    if (p1.y > p2.y)
    {
        std::swap(p1, p2);
    }
    
    //refuse to draw triangle if triangle is arealess. Assuming here that facets are superthin
    if (p0.y == p2.y)
    {
        return;
    }

    // Determine whether the short side is on the left or on the right.
    //In general there are 2 classes of triangles: by which side bend is
    bool shortside = (p1.y - p0.y) * (p2.x - p0.x) < (p1.x - p0.x) * (p2.y - p0.y); // false=left side, true=right side

    // Create two slopes: p0-p1 (short) and p0-p2 (long).
    // One of these is on the left side and one is on the right side.
    // At y = y1, the p0-p1 slope will be replaced with p1-p2 slope.
    std::vector<GLMSlope> sides(2);
    sides[!shortside] = GLMSlope(p0, p2, p2.y - p0.y);

    for (float y = p0.y, endy = p0.y; ; ++y)
    {
        if (y >= endy)
        {
            // If y of B is reached, the triangle is complete.
            if (y >= p2.y)
            {
                break;
            }
            //Recalculate slope for short side. Number of lines cannot be zero
            sides[shortside] = y < p1.y ?
            GLMSlope(p0, p1, (endy = p1.y) - p0.y)
            :
            GLMSlope(p1, p2, (endy = p2.y) - p1.y);
        }
        this->process_scanline(y, sides[0], sides[1]);
    }
}

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

        if (ControlSystem::Buffer::depth_buffer[y][x0] < p0.z && p0.z > 0.1f) //facet is not behind camera so > 0.1f
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