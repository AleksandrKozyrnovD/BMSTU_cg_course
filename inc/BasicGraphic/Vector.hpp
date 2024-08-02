#include "Vector.h"
#include "glm/glm/ext/vector_float3.hpp"


Vector::Vector(float x, float y, float z)
    : direction(x, y, z)
{
    this->normalize();
}

Vector::Vector(const glm::vec3& direction)
    : direction(direction)
{
    this->normalize();
}

Vector& Vector::operator=(const Vector& direction)
{
    this->direction = direction.direction;
    this->normalize();
    return *this;
}

Vector& Vector::operator=(Vector&& direction)
{
    this->direction = direction.direction;
    this->normalize();
    return *this;
}

glm::vec3& Vector::getDirection()
{
    return this->direction;
}

void Vector::setDirection(const glm::vec3& direction)
{
    this->direction = direction;
}

Vector& Vector::normalize()
{
    this->direction = glm::normalize(this->direction);

    return *this;
}

float Vector::dot(const Vector& other) const
{
    return glm::dot(this->direction, other.direction);
}

Vector Vector::cross(const Vector& other) const
{
    return Vector(glm::cross(this->direction, other.direction));
}

float Vector::operator*(const Vector& other) const
{
    return this->dot(other);
}

Vector Vector::operator&(const Vector& other) const
{
    return this->cross(other);
}

void Vector::scale(float scalar)
{
    this->direction *= scalar;
}

Vector Vector::operator*(float scalar) const
{
    Vector other = Vector(*this);
    other.scale(scalar);
    return other;
}

Vector& Vector::operator*=(float scalar)
{
    this->scale(scalar);
    return *this;
}

Vector Vector::operator+(const Vector& other) const
{
    return Vector(this->direction + other.direction);
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(this->direction - other.direction);
}

Vector& Vector::operator+=(const Vector& other)
{
    this->direction += other.direction;
    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    this->direction -= other.direction;
    return *this;
}


float Vector::length() const
{
    return glm::length(this->direction);
}