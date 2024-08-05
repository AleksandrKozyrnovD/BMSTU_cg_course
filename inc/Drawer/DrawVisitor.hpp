#include "Canvas.h"
#include "DrawVisitor.h"
#include "CompositeObject.h"
#include "Model.h"
#include "glm/ext/matrix_projection.hpp"


DrawVisitor::DrawVisitor(std::shared_ptr<Camera>& camera)
    : camera(camera)
{}

void DrawVisitor::draw_facet(const Facet& facet)
{
    glm::mat4x4 model = this->transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, 1280.0f, 720.0f);

    

    glm::vec3 A = facet.A;
    glm::vec3 B = facet.B;
    glm::vec3 C = facet.C;

    A = view * glm::vec4(A, 1.0f);
    B = view * glm::vec4(B, 1.0f);
    C = view * glm::vec4(C, 1.0f);

    A = glm::project(A, model, projection, viewport);
    B = glm::project(B, model, projection, viewport);
    C = glm::project(C, model, projection, viewport);

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