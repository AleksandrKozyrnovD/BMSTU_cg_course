#include "Canvas.h"
#include "DrawVisitor.h"
#include "CompositeObject.h"
#include "Model.h"
#include "glm/ext/matrix_projection.hpp"
#include "glm/geometric.hpp"
#include "glm/glm/ext/vector_float4.hpp"



DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : camera(camera)
{}

#include <iostream>
void DrawVisitor::draw_facet(const Facet& facet)
{
    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    //check if normal from facet is looking towards camera. Normal is in local coordinates so need to transform it
    glm::vec3 normal = glm::normalize(view * glm::vec4(facet.normal, 0.0f));

    std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    std::cout << camera->forward.x << " " << camera->forward.y << " " << camera->forward.z << std::endl;
    std::cout << "==========" << std::endl;
    if (glm::dot(normal, glm::vec3(0.0f, 0.0f, 1.0f)) < 0.0f)
    {
        return;
    }


    glm::vec3 A = glm::vec3(model * glm::vec4(facet.A, 1.0f));
    glm::vec3 B = glm::vec3(model * glm::vec4(facet.B, 1.0f));
    glm::vec3 C = glm::vec3(model * glm::vec4(facet.C, 1.0f));


    A = glm::vec3(glm::project(A, projection, view, viewport));
    B = glm::vec3(glm::project(B, projection, view, viewport));
    C = glm::vec3(glm::project(C, projection, view, viewport));


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
        this->draw_facet(facet);
    }
}


void DrawVisitor::visit(Camera& obj)
{
    return;
}


void DrawVisitor::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<DrawVisitor>(this->camera));
}