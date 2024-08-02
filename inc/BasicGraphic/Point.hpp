#include "Point.h"

#pragma region constructors
Point::Point(const Point& other)
: position(other.position), color(other.color)
{}

Point::Point(Point&& other) noexcept
: position(std::move(other.position)), color(std::move(other.color))
{}

Point::Point(const glm::vec4& pos, const glm::vec4& color) noexcept
: position(pos), color(color)
{}

Point::Point(const glm::vec4& pos) noexcept
: position(pos), color(glm::vec4(1, 1, 1, 1))
{}

#pragma endregion constructors


// Point& Point::operator+(const Point& other)
// {
//     this->position += other.position;

//     return *this;
// }

Point Point::operator+(const Point& other) const
{
    Point newpoint(*this);
    newpoint.position = this->position + other.position;
    
    return newpoint;
}

// Point& Point::operator-(const Point& other)
// {
//     this->position -= other.position;

//     return *this;
// }

Point Point::operator-(const Point& other) const
{
    Point newpoint(*this);
    newpoint.position = this->position - other.position;
    
    return newpoint;
}


// Point& Point::operator^(const Point& other)
// {
//     //relativistic sum of two color. (light speed equation)
//     this->color = (this->color + other.color)
//                 / (glm::vec4(1,1,1,1) + this->color * other.color);

//     return *this;
// }

Point Point::operator^(const Point& other) const
{
    Point newpoint = *this ^ other;
    
    return newpoint;
}

// Point& Point::operator|(const Point& other)
// {
//     //relativistic substraction of two color. (light speed equation)
//     this->color = (this->color - other.color)
//                 / (glm::vec4(1,1,1,1) - this->color * other.color);

//     return *this;
// }


Point Point::operator|(const Point& other) const
{
    Point newpoint = *this | other;
    
    return newpoint;
}

Point& Point::operator=(const Point& other)
{
    this->position = other.position;
    this->color = other.color;

    return *this;
}

Point& Point::operator=(Point&& other) noexcept
{
    this->position = std::move(other.position);
    this->color = std::move(other.color);

    return *this;
}