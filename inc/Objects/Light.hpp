#include "Camera.h"
#include "Light.h"


Light::Light(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward, const glm::vec4& color)
    : Camera(center, up, forward), color(color)
{}

Light::Light(const Camera& camera, const glm::vec4& color)
    : Camera(camera), color(color)
{}


void Light::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}
