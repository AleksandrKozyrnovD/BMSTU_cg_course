#include "ModelType/Facet.h"
#include "RotateVisitor.h"

#include "../Objects/Model.h"
#include "../Objects/Camera.h"
#include "../Objects/CompositeObject.h"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/ext/vector_float4.hpp"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm/gtx/rotate_vector.hpp>

RotateVisitor::RotateVisitor(double x, double y, double z)
    : TransformVisitor(x, y, z)
{}

void RotateVisitor::visit(Model& obj)
{
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    glm::vec3 center = obj.get_center();
    // translate to center
    matrix = glm::translate(matrix, -center);
    for (Facet& facet : obj.model->get_surfaces())
    {
        facet.transform(matrix);       
    }

    matrix = glm::mat4x4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (Facet& facet : obj.model->get_surfaces())
    {
        facet.transform(matrix);       
    }

    // back to where it was
    matrix = glm::translate(glm::mat4x4(1.0f), center);
    for (Facet& facet : obj.model->get_surfaces())
    {
        facet.transform(matrix);       
    }

    // obj.transform = matrix * obj.transform;

    
    // obj.center = matrix * glm::vec4(obj.center, 1.0f);
}

void RotateVisitor::visit(Camera& obj)
{
    glm::vec3 rotator = this->coordinate;
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(rotator.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // obj.center = matrix * glm::vec4(obj.center, 1.0f);
}

void RotateVisitor::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<RotateVisitor>(*this));
}