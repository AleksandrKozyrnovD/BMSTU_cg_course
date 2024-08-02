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
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(this->coordinate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    for (Facet& facet : obj.model->get_surfaces())
    {
        facet.transform(matrix);       
    }
    
    obj.center.position = matrix * obj.center.position;
}

void RotateVisitor::visit(Camera& obj)
{
    glm::vec3 scale = this->coordinate;
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(scale.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(scale.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(scale.z), glm::vec3(0.0f, 0.0f, 1.0f));

    obj.center.position = matrix * obj.center.position;
}

void RotateVisitor::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<RotateVisitor>(*this));
}