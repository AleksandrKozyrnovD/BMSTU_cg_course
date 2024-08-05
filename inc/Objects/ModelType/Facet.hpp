#include "Facet.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm/gtx/rotate_vector.hpp>
#include <glm/glm/mat4x4.hpp>

Facet::Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) noexcept
    : Surface(A, B, C)
{}

Facet::Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, bool direction) noexcept
    : Surface(A, B, C, direction)
{}

Facet& Facet::operator=(const Facet& other)
{
    this->A = other.A;
    this->B = other.B;
    this->C = other.C;
    this->normal = other.normal;

    return *this;
}

Facet& Facet::operator=(Facet&& other) noexcept
{
    this->A = std::move(other.A);
    this->B = std::move(other.B);
    this->C = std::move(other.C);
    this->normal = std::move(other.normal);

    return *this;
}


void Facet::move(const glm::vec3& vector)
{
    A += vector;
    B += vector;
    C += vector;
}

void Facet::scale(const glm::vec3& scale)
{
    A *= scale;
    B *= scale;
    C *= scale;
}

void Facet::scale(float scalar)
{
    this->scale(glm::vec3(scalar));
}

void Facet::rotate(const glm::vec3 angles)
{
    //identity matrix
    glm::mat4x4 matrix = glm::mat4x4(1.0f);

    //rotate for all angles
    matrix = glm::rotate(matrix, glm::radians(angles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(angles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(angles.z), glm::vec3(0.0f, 0.0f, 1.0f));

    //apply matrix
    A = matrix * glm::vec4(A, 1.0f);
    B = matrix * glm::vec4(B, 1.0f);
    C = matrix * glm::vec4(C, 1.0f);
}

glm::vec3 Facet::get_center() const
{
    return (A + B + C) / 3.0f;
}

void Facet::transform(const glm::mat4x4& matrix)
{
    A = matrix * glm::vec4(A, 1.0f);
    B = matrix * glm::vec4(B, 1.0f);
    C = matrix * glm::vec4(C, 1.0f);
}

void Facet::fix_direction(const glm::vec3& center)
{
    //get vector from center to A
    //if vector from center to A kinda looking towards normal, do nothing
    //else flip normal
    glm::vec3 center_A = center - A;

    if (glm::dot(center_A, this->normal) < 0.0f)
    {
        this->change_direction();
    }
}
