#include "Plane.h"

#include <glm/glm/geometric.hpp>

Surface::Surface(const Surface& other)
: A(other.A), B(other.B), C(other.C), normal(other.normal)
{}

Surface::Surface(Surface&& other) noexcept
: A(std::move(other.A)), B(std::move(other.B)), C(std::move(other.C)), normal(std::move(other.normal))
{}

Surface::Surface(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) noexcept
: A(A), B(B), C(C)
{
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;

    this->normal = glm::normalize(glm::cross(AB, AC));
}


Surface::Surface(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, bool direction) noexcept
: A(A), B(B), C(C)
{
    glm::vec3 AB = glm::vec3(B - A);
    glm::vec3 AC = glm::vec3(C - A);

    if (direction)
    {
        this->normal = glm::normalize(glm::cross(AB, AC));
    }
    else
    {
        this->normal = glm::normalize(glm::cross(AB, AC)) * (-1.0f);
    }
}

const glm::vec3& Surface::get_normal() const
{
    return this->normal;
}

const glm::vec3& Surface::operator*() const
{
    return this->get_normal();
}


void Surface::change_direction()
{
    this->normal *= -1.0f;
}
