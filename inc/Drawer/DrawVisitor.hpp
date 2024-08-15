#include "Color.h"
#include "DrawVisitor.h"

#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"


DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : camera(camera)
{}


void DrawVisitor::rasterize_facet(const Facet& facet)
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
    float z0 = p0.z;
    float z1 = p1.z;
    float z2 = p2.z;

    //project
    p0 = glm::vec3(glm::project(p0, glm::mat4x4(1.0f), projection, viewport));
    p1 = glm::vec3(glm::project(p1, glm::mat4x4(1.0f), projection, viewport));
    p2 = glm::vec3(glm::project(p2, glm::mat4x4(1.0f), projection, viewport));


    //apply z
    p0.z = z0;
    p1.z = z1;
    p2.z = z2;


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

            // sides[shortside] = y < p1.y ?
            // Slope(x0, x1, (endy = y1) - y0)
            // :
            // Slope(x1, x2, (endy = y2) - y1);
        }
        //draw scanline
        this->draw_scanline(y, sides[0], sides[1], facet.color);
    }
}

#include <iostream>
void DrawVisitor::draw_scanline(float y, GLMSlope& A, GLMSlope& B, uint32_t color)
{
    glm::vec3 p0 = A.get();
    glm::vec3 p1 = B.get();


    int x0 = p0.x;
    int x1 = p1.x;

    if (x0 < 0 && x1 < 0) return;
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
            ControlSystem::Buffer::frame_buffer[y][x0] = color;
            ControlSystem::Buffer::depth_buffer[y][x0] = p0.z;
        }
    }

    A.advance();
    B.advance();
}


// #include <iostream>
// void DrawVisitor::rasterize_facet(const Facet& facet)
// {
    // glm::mat4x4 model = this->transform;
    // glm::mat4x4 projection = camera->get_perspective_matrix();
    // glm::mat4x4 view = camera->get_view_matrix();
    // glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    // //check if normal from facet is looking towards camera. Normal is in local coordinates so need to transform it
    // glm::vec3 normal = glm::normalize(view * glm::vec4(facet.normal, 0.0f));

    // std::cout << "Value: " << glm::dot(normal, this->camera->forward) << std::endl;
    // std::cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
    // std::cout << "Camera: " << camera->forward.x << " " << camera->forward.y << " " << camera->forward.z << std::endl;
    // // if vectors are facing in the same directions, it means that this facet is behind center to which he relates
    // if (glm::dot(normal, this->camera->forward) < 0.0f)
    // {
    //     return;
    // }


    // glm::vec3 A = glm::vec3(view * glm::vec4(facet.A, 1.0f));
    // glm::vec3 B = glm::vec3(view * glm::vec4(facet.B, 1.0f));
    // glm::vec3 C = glm::vec3(view * glm::vec4(facet.C, 1.0f));

    // //check if any point is behind the camera
    // // if (glm::dot(A, this->camera->forward) < 0.0f ||
    // //     glm::dot(B, this->camera->forward) < 0.0f ||
    // //     glm::dot(C, this->camera->forward) < 0.0f)
    // // {
    // //     return;
    // // }
    // A = glm::vec3(glm::project(A, model, projection, viewport));
    // B = glm::vec3(glm::project(B, model, projection, viewport));
    // C = glm::vec3(glm::project(C, model, projection, viewport));



    // std::cout << "A: " << A.x << " " << A.y << " " << A.z << std::endl;
    // std::cout << "B: " << B.x << " " << B.y << " " << B.z << std::endl;
    // std::cout << "C: " << C.x << " " << C.y << " " << C.z << std::endl;
    // std::cout << "=========" << std::endl;

    // //check if any of the points are outside the screen
    // if (A.x < 0 || A.x > 1280 || A.y < 0 || A.y > 720 ||
    //     B.x < 0 || B.x > 1280 || B.y < 0 || B.y > 720 ||
    //     C.x < 0 || C.x > 1280 || C.y < 0 || C.y > 720)
    // {
    //     return;
    // }


    // Graphics::SDLCanvas::set_color(255, 255, 255, 255);

    // Graphics::SDLCanvas::draw_line(A.x, A.y, B.x, B.y);
    // Graphics::SDLCanvas::draw_line(B.x, B.y, C.x, C.y);
    // Graphics::SDLCanvas::draw_line(C.x, C.y, A.x, A.y);
// }

void DrawVisitor::visit(Model& obj)
{
    this->transform = obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->rasterize_facet(facet);
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