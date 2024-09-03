#include "ModelType/Facet.h"
#include "MoveVisitor.h"

#include "../Objects/Model.h"
#include "../Objects/Camera.h"
#include "../Objects/CompositeObject.h"
#include "Light.h"

#include "glm/geometric.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/ext/vector_float4.hpp"

MoveVisitor::MoveVisitor(double x, double y, double z)
    : TransformVisitor(x, y, z)
{}

void MoveVisitor::visit(Model& obj)
{
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    transform = glm::translate(transform, this->coordinate);
    obj.transform = transform * obj.transform;
}

void MoveVisitor::visit(Camera& obj)
{
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    transform = glm::translate(transform, this->coordinate);

    obj.center = glm::vec3(transform * glm::vec4(obj.center, 1.0f));
}

void MoveVisitor::visit(Light& obj)
{
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    transform = glm::translate(transform, this->coordinate);

    obj.center = glm::vec3(transform * glm::vec4(obj.center, 1.0f));
}

void MoveVisitor::visit(CompositeObject& obj)
{
    // obj.accept(std::make_shared<MoveVisitor>(*this));
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    transform = glm::translate(transform, this->coordinate);
    obj.transform = transform * obj.transform;
}
