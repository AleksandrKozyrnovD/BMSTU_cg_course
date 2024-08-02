#ifndef __POINT_H__
#define __POINT_H__

#include <glm/glm/vec4.hpp>
#include <glm/glm/vec3.hpp>


struct Point
{
public:
    Point() = default;
    Point(const Point& other);
    Point(Point&& other) noexcept;

    Point(const glm::vec4& pos, const glm::vec4& color) noexcept;
    Point(const glm::vec4& pos) noexcept; 

    ~Point() = default;

    Point& operator=(const Point& other);
    Point& operator=(Point&& other) noexcept;

    //position operators
    // Point& operator+(const Point& other);
    Point operator+(const Point& other) const;
    // Point& operator-(const Point& other);
    Point operator-(const Point& other) const;

    //color operators
    // Point& operator^(const Point& other);     //add colors
    Point operator^(const Point& other) const;
    // Point& operator|(const Point& other);     //substract colors
    Point operator|(const Point& other) const;
    
public:
    glm::vec4 position;
    glm::vec4 color;
};

#include "Point.hpp"

#endif