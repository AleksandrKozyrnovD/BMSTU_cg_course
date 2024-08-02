#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <glm/glm/geometric.hpp>
#include <glm/glm/vec3.hpp>


struct Vector
{
public:
    Vector() = default;
    explicit Vector(const Vector& other) = default;
    Vector(Vector&& other) = default;

    Vector(float x, float y, float z);
    explicit Vector(const glm::vec3& direction);

    ~Vector() = default;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);


    glm::vec3& getDirection();
    void setDirection(const glm::vec3& direction);

    float length() const;
    Vector& normalize();

    Vector cross(const Vector& other) const;
    Vector operator&(const Vector& other) const; //cross

    float dot(const Vector& other) const;
    float operator*(const Vector& other) const; //dot

    void scale(float scalar);
    Vector operator*(float scalar) const;
    Vector& operator*=(float scalar);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);

public:
    glm::vec3 direction;
};

#include "Vector.hpp"

#endif