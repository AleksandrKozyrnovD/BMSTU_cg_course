#include "Facet.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm/gtx/rotate_vector.hpp>
#include <glm/glm/mat4x4.hpp>

Facet::Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, uint32_t color) noexcept
    : Surface(A, B, C), color(color)
{}

Facet::Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, bool direction, uint32_t color) noexcept
    : Surface(A, B, C, direction), color(color)
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

    this->normal = glm::normalize(matrix * glm::vec4(this->normal, 0.0f));
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

    this->normal = glm::normalize(matrix * glm::vec4(this->normal, 0.0f));
}

#include <iostream>
void Facet::fix_direction(const glm::vec3& center)
{
    //get vector from center to A
    //if vector from center to A kinda looking towards normal, do nothing
    //else flip normal
    glm::vec3 center_A = center - this->get_center();

    std::cout << "===========" << std::endl;
    std::cout << "Center: " << center.x << ", " << center.y << ", " << center.z << std::endl;
    std::cout << "Normal bef: " << this->normal.x << ", " << this->normal.y << ", " << this->normal.z << std::endl;
    std::cout << "Point A: " << A.x << ", " << A.y << ", " << A.z << std::endl;
    std::cout << "Point B: " << B.x << ", " << B.y << ", " << B.z << std::endl;
    std::cout << "Point C: " << C.x << ", " << C.y << ", " << C.z << std::endl;
    std::cout << "CenterA: " << center_A.x << ", " << center_A.y << ", " << center_A.z << std::endl;
    std::cout << "Res: " << glm::dot(center_A, this->normal) << std::endl;

    //ARGB888
    int r, g, b, a;
    uint32_t color = this->color;
    r = (color & 0xFF000000) >> 24;
    g = (color & 0x00FF0000) >> 16;
    b = (color & 0x0000FF00) >> 8;
    a = (color & 0x000000FF);
    std::cout << "Color: " << r << ", " << g << ", " << b << ", " << a << ", " << color << std::endl;
    if (glm::dot(center_A, this->normal) < 0.0f)
    {
        this->change_direction();
        std::cout << "Normal aft: " << this->normal.x << ", " << this->normal.y << ", " << this->normal.z << std::endl;
        std::cout << "!!!Direction flipped!!!" << std::endl;
    }
}
