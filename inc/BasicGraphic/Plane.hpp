#include "BasicGraphic/Plane.h"
#include "Vector.h"

#include <glm/glm/geometric.hpp>

Surface::Surface(const Surface& other)
: A(other.A), B(other.B), C(other.C), normal(other.normal)
{}

Surface::Surface(Surface&& other) noexcept
: A(std::move(other.A)), B(std::move(other.B)), C(std::move(other.C)), normal(std::move(other.normal))
{}

Surface::Surface(const Point& A, const Point& B, const Point& C) noexcept
: A(A), B(B), C(C)
{
    Vector AB = Vector(B.position - A.position);
    Vector AC = Vector(C.position - A.position);

    this->normal = (AB & AC).normalize();
}


Surface::Surface(const Point& A, const Point& B, const Point& C, bool direction) noexcept
: A(A), B(B), C(C)
{
    Vector AB = Vector(B.position - A.position);
    Vector AC = Vector(C.position - A.position);

    if (direction)
    {
        this->normal = (AB & AC).normalize();
    }
    else
    {
        this->normal = (AB & AC).normalize() * (-1.0f);
    }
}

const Vector& Surface::get_normal() const
{
    return this->normal;
}

const Vector& Surface::operator*() const
{
    return this->get_normal();
}


void Surface::change_direction()
{
    this->normal *= -1.0f;
}
