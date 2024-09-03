#include "ModelType/Facet.h"
#include "RotateVisitor.h"

#include "../Objects/Model.h"
#include "../Objects/Camera.h"
#include "../Objects/CompositeObject.h"
#include "Light.h"
#include "glm/geometric.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/ext/vector_float4.hpp"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm/gtx/rotate_vector.hpp>

RotateVisitor::RotateVisitor(double x, double y, double z)
    : TransformVisitor(x, y, z)
{}

void RotateVisitor::visit(Model& obj)
{
    // glm::mat4x4 matrix = glm::mat4x4(1.0f);
    // glm::vec3 center = obj.get_center();
    // // translate to center
    // matrix = glm::translate(matrix, -center);
    // for (Facet& facet : obj.model->get_surfaces())
    // {
    //     facet.transform(matrix);       
    // }

    // matrix = glm::mat4x4(1.0f);
    // matrix = glm::rotate(matrix, glm::radians(this->coordinate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    // matrix = glm::rotate(matrix, glm::radians(this->coordinate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    // matrix = glm::rotate(matrix, glm::radians(this->coordinate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // for (Facet& facet : obj.model->get_surfaces())
    // {
    //     facet.transform(matrix);       
    // }

    // // back to where it was
    // matrix = glm::translate(glm::mat4x4(1.0f), center);
    // for (Facet& facet : obj.model->get_surfaces())
    // {
    //     facet.transform(matrix);       
    // }

    glm::vec3 center = glm::vec3(obj.transform * glm::vec4(obj.get_center(), 1.0f));
    glm::mat4 move_to_center = glm::translate(glm::mat4(1.0f), -center);

    glm::mat4 rotate = glm::mat4(1.0f);
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 move_to_origin = glm::translate(glm::mat4(1.0f), center);

    glm::mat4 transform = move_to_origin * rotate * move_to_center;
    obj.transform = transform * obj.transform;
}

void RotateVisitor::visit(Camera& obj)
{
    glm::vec3 rotator = this->coordinate;
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(rotator.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.z), glm::vec3(0.0f, 0.0f, 1.0f));


    obj.forward = glm::normalize(matrix * glm::vec4(obj.forward, 0.0f));
    obj.right = glm::normalize(glm::cross(obj.forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    obj.up = glm::normalize(glm::cross(obj.right, obj.forward));

    // obj.up = glm::normalize(matrix * glm::vec4(obj.up, 0.0f));
    // obj.right = glm::normalize(matrix * glm::vec4(obj.right, 0.0f));
}

void RotateVisitor::visit(Light& obj)
{
    glm::vec3 rotator = this->coordinate;
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(rotator.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotator.z), glm::vec3(0.0f, 0.0f, 1.0f));


    obj.up = glm::normalize(matrix * glm::vec4(obj.up, 0.0f));
    obj.forward = glm::normalize(matrix * glm::vec4(obj.forward, 0.0f));
    obj.right = glm::normalize(matrix * glm::vec4(obj.right, 0.0f));
}

void RotateVisitor::visit(CompositeObject& obj)
{
    glm::vec3 center = glm::vec3(obj.transform * glm::vec4(obj.get_center(), 1.0f));
    glm::mat4 move_to_center = glm::translate(glm::mat4(1.0f), -center);

    glm::mat4 rotate = glm::mat4(1.0f);
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(this->coordinate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 move_to_origin = glm::translate(glm::mat4(1.0f), center);

    glm::mat4 transform = move_to_origin * rotate * move_to_center;
    obj.transform = transform * obj.transform;
}