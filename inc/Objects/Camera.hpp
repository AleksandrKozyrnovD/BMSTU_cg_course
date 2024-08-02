#include "Camera.h"

Camera::Camera(double x, double y, double z)
    // : center(glm::vec4(x, y, z, 1.0f))
{
    this->center = Point(glm::vec4(x, y, z, 1.0f));

    this->up = Vector(0, 1, 0);
    this->forward = Vector(0, 0, 1);
    this->right = Vector(1, 0, 0);
}

Camera::Camera(const Point& center)
    // : center(center)
{
    this->center = center;

    this->up = Vector(0, 1, 0);
    this->forward = Vector(0, 0, 1);
    this->right = Vector(1, 0, 0);
}

Camera::Camera(const Point& center, const Vector& up, const Vector& forward)
    : up(up), forward(forward)
{
    this->center = center;
    this->right = up & forward;
}

void Camera::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}