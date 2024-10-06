#include "Camera.h"
#include "Light.h"


Light::Light(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward, const uint32_t& color)
    : Camera(center, up, forward), color(color)
{
    this->fov = 45;
}

Light::Light(const Camera& camera, const uint32_t& color)
    : Camera(camera), color(color)
{
    this->fov = 45;
}


void Light::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}

glm::mat4x4 Light::get_perspective_matrix() const
{
    return glm::perspective(glm::radians(this->fov), 1.0f, 0.1f, 10.0f);
}
