#ifndef __PLANE_H__
#define __PLANE_H__

#include "Point.h"
#include "Vector.h"


class Surface
{
public:
    Surface() = default;
    explicit Surface(const Surface& other);
    Surface(Surface&& other) noexcept;
    
    Surface(const Point& A, const Point& B, const Point& C) noexcept;
    Surface(const Point& A, const Point& B, const Point& C, bool direction) noexcept;

    ~Surface() = default;

    Surface& operator=(const Surface& other);

    const Vector& get_normal() const;
    const Vector& operator*() const;

    void change_direction();

protected:
    Point A, B, C;
    Vector normal;
};

#include "Plane.hpp"

#endif