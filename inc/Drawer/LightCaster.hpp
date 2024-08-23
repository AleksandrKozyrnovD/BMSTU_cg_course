#include "LightCaster.h"


#include "Buffer.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "Model.h"
#include "CompositeObject.h"
#include "glm/ext/matrix_projection.hpp"
#include "glm/matrix.hpp"


LightCaster::LightCaster(std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light)
    : Drawer(camera), light_source(light)
{}

void LightCaster::process_facet(const Facet& facet)
{
    /*
    https://bisqwit.iki.fi/jutut/kuvat/programming_examples/polytut/ <---- tutorial and prime example from where i got code
    */

    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = this->light_source->get_perspective_matrix();
    glm::mat4x4 view = this->light_source->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    glm::vec3 p0 = facet.A;
    glm::vec3 p1 = facet.B;
    glm::vec3 p2 = facet.C;

    glm::mat4 proj = projection * view;

    //project
    p0 = glm::vec3(glm::project(p0, model, proj, viewport));
    p1 = glm::vec3(glm::project(p1, model, proj, viewport));
    p2 = glm::vec3(glm::project(p2, model, proj, viewport));



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
        if (ControlSystem::Buffer::light_depth_buffer[y][x0] < p0.z && p0.z > 0.1f) //facet is not behind camera so > 0.1f
        {
            ControlSystem::Buffer::light_depth_buffer[y][x0] = p0.z;
            ControlSystem::Buffer::light_frame_buffer[y][x0] = this->color;
        }
    }

    A.advance();
    B.advance();
}

// #include <iostream>
// void LightCaster::see_from_viewer()
// {
//     glm::mat4 camera_view = camera->get_view_matrix();
//     glm::mat4 camera_perspective = camera->get_perspective_matrix();
//     glm::mat4 light_view = light_source->get_view_matrix();
//     glm::mat4 light_perspective = light_source->get_perspective_matrix();

//     glm::mat4 camera_proj = camera_perspective * camera_view;
//     glm::mat4 light_proj = light_perspective * light_view;

//     int w = 1280;
//     int h = 720;
//     glm::vec4 viewport(0.0f, 0.0f, w, h);

//     for (int y = 0; y < 720; ++y)
//     {
//         for (int x = 0; x < 1280; ++x)
//         {
//             float z = ControlSystem::Buffer::depth_buffer[y][x];
//             // std::cout << "Initial z: " << z << std::endl;
//             if (true) //if not infinitely far away
//             {
//                 glm::vec3 lightdepthbufferpoint = glm::vec3(x, y, z);
                
//                 //to get the point in world coordinates
//                 lightdepthbufferpoint = glm::unProject(lightdepthbufferpoint, this->transform, camera_proj, viewport);

//                 //now to get the point in light coordinates
//                 lightdepthbufferpoint = glm::project(lightdepthbufferpoint, this->transform, light_proj, viewport);
//                 int x2 = round(lightdepthbufferpoint.x);
//                 int y2 = round(lightdepthbufferpoint.y);
//                 float z2 = lightdepthbufferpoint.z;

//                 if (x2 >= 0 && x2 < 1280 && y2 >= 0 && y2 < 720)
//                 {
//                     // std::cout << "x,y: " << x2 << " " << y2 << " z: " << z2 << std::endl;
//                     // std::cout << "Buffer z: " << ControlSystem::Buffer::light_depth_buffer[y2][x2] << std::endl;
//                     //if z is not far from shadowmap's z
//                     if (fabs(ControlSystem::Buffer::light_depth_buffer[y2][x2] - 0) >= 0.000f)
//                     {
//                         // std::cout << "Got it!" << std::endl;
//                         ControlSystem::Buffer::frame_buffer[y][x] = this->color;
//                     }
//                 }
//                 // std::cout << "========" << std::endl;
//             }
//         }
//     }
// }


void LightCaster::visit(Model& obj)
{
    this->transform = obj.transform;
    for (const Facet& facet : obj.model->get_surfaces())
    {
        this->process_facet(facet);
        this->color = facet.color;
        // this->see_from_viewer();
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