#ifndef __FACET_H__
#define __FACET_H__

#include "Plane.h"
#include "glm/mat4x4.hpp"

#include "Point.h"

class Facet : public Surface
{
public:
    Facet() = default;
    Facet(const Facet& other) = default;
    Facet(Facet&& other) noexcept = default;
    
    Facet(const Point& A, const Point& B, const Point& C) noexcept;
    Facet(const Point& A, const Point& B, const Point& C, bool direction) noexcept;

    ~Facet() = default;

    Facet& operator=(const Facet& other);
    Facet& operator=(Facet&& other) noexcept;

    void move(const glm::vec4& delta);
    void rotate(const glm::vec3 angles);
    void scale(const glm::vec3& scale);
    void scale(float scalar);

    void transform(const glm::mat4x4& transformation);

    Point get_center() const;

    void fix_direction(const Point& center);
};

#include "Facet.hpp"

#endif