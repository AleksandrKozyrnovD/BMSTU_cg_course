#include "ModelType/Facet.h"
#include "ScaleVisitor.h"

#include "../Objects/Model.h"
#include "../Objects/Camera.h"
#include "../Objects/CompositeObject.h"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/ext/vector_float4.hpp"

ScaleVisitor::ScaleVisitor(double x, double y, double z)
    : TransformVisitor(x, y, z)
{}

void ScaleVisitor::visit(Model& obj)
{
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    //tramslate then scale then translate again
    // transform = glm::translate(transform, obj.get_center());
    transform = glm::scale(transform, this->coordinate);
    // transform = glm::translate(transform, -obj.get_center());

    obj.transform = transform * obj.transform;
    // for (Facet& facet : obj.model->get_surfaces())
    // {
    //     facet.transform(transform);       
    // }

    // obj.center = transform * glm::vec4(obj.center, 1.0f);
}

void ScaleVisitor::visit(Camera& obj)
{}

void ScaleVisitor::visit(Light& obj)
{}

void ScaleVisitor::visit(CompositeObject& obj)
{
    // obj.accept(std::make_shared<ScaleVisitor>(*this));
    glm::mat4x4 transform = glm::mat4x4(1.0f);
    transform = glm::scale(transform, this->coordinate);
    obj.transform = transform * obj.transform;
}