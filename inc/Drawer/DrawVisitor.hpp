#include "Canvas.h"
#include "DrawVisitor.h"
#include "CompositeObject.h"
#include "Model.h"
#include "glm/ext/matrix_projection.hpp"
#include "glm/geometric.hpp"
#include "glm/glm/ext/vector_float4.hpp"
#include "glm/vector_relational.hpp"



DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : camera(camera)
{}

#include <iostream>
void DrawVisitor::rasterize_facet(const Facet& facet)
{
    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    //check if normal from facet is looking towards camera. Normal is in local coordinates so need to transform it
    glm::vec3 normal = glm::normalize(view * glm::vec4(facet.normal, 0.0f));

    std::cout << "Value: " << glm::dot(normal, this->camera->forward) << std::endl;
    std::cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
    std::cout << "Camera: " << camera->forward.x << " " << camera->forward.y << " " << camera->forward.z << std::endl;
    // if vectors are facing in the same directions, it means that this facet is behind center to which he relates
    if (glm::dot(normal, this->camera->forward) < 0.0f)
    {
        return;
    }


    glm::vec3 A = glm::vec3(view * glm::vec4(facet.A, 1.0f));
    glm::vec3 B = glm::vec3(view * glm::vec4(facet.B, 1.0f));
    glm::vec3 C = glm::vec3(view * glm::vec4(facet.C, 1.0f));

    // std::cout << "A: " << A.x << " " << A.y << " " << A.z << std::endl;
    // std::cout << "B: " << B.x << " " << B.y << " " << B.z << std::endl;
    // std::cout << "C: " << C.x << " " << C.y << " " << C.z << std::endl;
    // std::cout << "===========================^^^^first^^^^" << std::endl;

    //check if any point is behind the camera
    // if (glm::dot(A, this->camera->forward) < 0.0f ||
    //     glm::dot(B, this->camera->forward) < 0.0f ||
    //     glm::dot(C, this->camera->forward) < 0.0f)
    // {
    //     return;
    // }
    A = glm::vec3(glm::project(A, model, projection, viewport));
    B = glm::vec3(glm::project(B, model, projection, viewport));
    C = glm::vec3(glm::project(C, model, projection, viewport));



    std::cout << "A: " << A.x << " " << A.y << " " << A.z << std::endl;
    std::cout << "B: " << B.x << " " << B.y << " " << B.z << std::endl;
    std::cout << "C: " << C.x << " " << C.y << " " << C.z << std::endl;
    std::cout << "=========" << std::endl;

    //check if any of the points are outside the screen
    if (A.x < 0 || A.x > 1280 || A.y < 0 || A.y > 720 ||
        B.x < 0 || B.x > 1280 || B.y < 0 || B.y > 720 ||
        C.x < 0 || C.x > 1280 || C.y < 0 || C.y > 720)
    {
        return;
    }


    Graphics::SDLCanvas::set_color(255, 255, 255, 255);

    Graphics::SDLCanvas::draw_line(A.x, A.y, B.x, B.y);
    Graphics::SDLCanvas::draw_line(B.x, B.y, C.x, C.y);
    Graphics::SDLCanvas::draw_line(C.x, C.y, A.x, A.y);
}

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