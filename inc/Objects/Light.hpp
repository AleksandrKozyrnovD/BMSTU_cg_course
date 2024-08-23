#include "Camera.h"
#include "Light.h"


Light::Light(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward, const uint32_t& color)
    : Camera(center, up, forward), color(color)
{
    this->fov = 90;
}

Light::Light(const Camera& camera, const uint32_t& color)
    : Camera(camera), color(color)
{
    this->fov = 90;
}


void Light::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}
