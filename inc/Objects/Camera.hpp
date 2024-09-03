#include "Buffer.inl"
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "DrawManager.h"

Camera::Camera()
    : up(0, 1, 0), forward(0, 0, 1), right(1, 0, 0)
{}

Camera::Camera(double x, double y, double z)
{
    this->center = glm::vec3(x, y, z);

    this->up = glm::vec3(0, 1, 0);
    this->forward = glm::vec3(0, 0, 1);
    this->right = glm::vec3(1, 0, 0);
}

Camera::Camera(const glm::vec3& center)
    // : center(center)
{
    this->center = center;

    this->up = glm::vec3(0, 1, 0);
    this->forward = glm::vec3(0, 0, 1);
    this->right = glm::vec3(1, 0, 0);
}

Camera::Camera(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward)
    : up(up), forward(forward)
{
    this->center = center;
    this->right = glm::cross(up, forward);
}

void Camera::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}


glm::mat4x4 Camera::get_view_matrix() const
{
    return glm::lookAt(this->center, this->center - this->forward, this->up);
}

glm::mat4x4 Camera::get_perspective_matrix() const
{
    float aspect = float(ControlSystem::Buffer::width) / float(ControlSystem::Buffer::height);
    return glm::perspective(glm::radians(this->fov), aspect, 0.1f, 10.0f);
}
