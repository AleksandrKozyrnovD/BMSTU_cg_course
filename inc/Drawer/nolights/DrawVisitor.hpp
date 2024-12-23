#include "DrawVisitor.h"

#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"

/*
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
DEPRECATED< NOT USED
*/


DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : Drawer(camera)
{}

#include <iostream>
void DrawVisitor::process_facet(const Facet& facet)
{
    /*
    https://bisqwit.iki.fi/jutut/kuvat/programming_examples/polytut/ <---- tutorial and prime example from where i got code
    */

    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, ControlSystem::Buffer::width, ControlSystem::Buffer::height);

    //back face culling. Normal is in local coordinates <<<!!!NOT!!!DONE!!!>>>
    // glm::vec3 normal = glm::normalize(this->transform * glm::vec4(facet.normal, 0.0f)); //in world coordinates
    // normal = glm::normalize(view * glm::vec4(normal, 0.0f)); //in camera coordinates
    // if (glm::dot(normal, camera->forward) <= 0.0f) return;

    glm::vec3 p0 = facet.A;
    glm::vec3 p1 = facet.B;
    glm::vec3 p2 = facet.C;


    glm::mat4 proj = projection * view;

    //project
    p0 = glm::vec3(glm::project(p0, model, proj, viewport));
    p1 = glm::vec3(glm::project(p1, model, proj, viewport));
    p2 = glm::vec3(glm::project(p2, model, proj, viewport));

    if (glm::isnan(p0.x) || glm::isnan(p0.y) || glm::isnan(p0.z) || glm::isnan(p1.x) || glm::isnan(p1.y) || glm::isnan(p1.z) || glm::isnan(p2.x) || glm::isnan(p2.y) || glm::isnan(p2.z))
    {
        return;
    }
    if (p0.z < 1.0f || p1.z < 1.0f || p2.z < 1.0f)
    {
        return;
    }

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

    std::cout << "======================" << std::endl;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            std::cout << model[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "x1: " << p0.x << " x2: " << p1.x << " x3: " << p2.x << std::endl;
    std::cout << "y1: " << p0.y << " y2: " << p1.y << " y3: " << p2.y << std::endl;
    std::cout << "z1: " << p0.z << " z2: " << p1.z << " z3: " << p2.z << std::endl;
    std::cout << "======================" << std::endl;

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


void DrawVisitor::process_scanline(float y, GLMSlope& A, GLMSlope& B)
{
    glm::vec3 p0 = A.get();
    glm::vec3 p1 = B.get();


    int x0 = p0.x;
    int x1 = p1.x;
    float z = p0.z;

    if (x0 > x1) std::swap(x0, x1);
    // float dz = (p1.z - p0.z) / (float)(x1 - x0);
    float dz = (p0.z - p1.z) / (float)(x0 - x1);

    //for future me to fix
    if (y < 0) y = 0;
    if (y >= ControlSystem::Buffer::height) y = ControlSystem::Buffer::height - 1;
    if (x0 < 0) x0 = 0;
    if (x1 >= ControlSystem::Buffer::width) x1 = ControlSystem::Buffer::width - 1;

    // if (y < 0)
    // {
    //     x0 += (x1 - x0) / (y - p0.y) * (-y);
    //     y = 0;
    // }
    // if (y >= ControlSystem::Buffer::height)
    // {
    //     x0 += (x1 - x0) * (ControlSystem::Buffer::height - 1 - y);
    //     y = ControlSystem::Buffer::height - 1;
    // }

    // if (x0 < 0)
    // {
    //     x0 = 0;
    // }
    // if (x1 >= ControlSystem::Buffer::width)
    // {
    //     x1 = ControlSystem::Buffer::width - 1;
    // }

    for (; x0 < x1; ++x0, z += dz)
    {
        if (ControlSystem::Buffer::depth_buffer[y][x0] < z && z > 0.1f && z < 10.0f) //facet is not behind camera so > 0.1f
        {
            ControlSystem::Buffer::frame_buffer[y][x0] = this->color;
            ControlSystem::Buffer::depth_buffer[y][x0] = z;
        }
    }

    A.advance();
    B.advance();
}


void DrawVisitor::visit(Model& obj)
{
    glm::mat4 back = this->transform;
    // this->transform = obj.transform * this->transform;
    this->transform *= obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->color = facet.color;
        this->process_facet(facet);
    }
    this->transform = back;
}


void DrawVisitor::visit(Camera& obj)
{
    return;
}


void DrawVisitor::visit(CompositeObject& obj)
{
    glm::mat4x4 back = this->transform;
    // this->transform = obj.transform * this->transform;
    this->transform *= obj.transform;
    for (auto& element : obj)
    {
        element->accept(std::make_shared<DrawVisitor>(*this));
    }
    this->transform = back;
}

void DrawVisitor::visit(Light& obj)
{
    return;
}