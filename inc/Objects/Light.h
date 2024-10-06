#ifndef __LIGHT_H
#define __LIGHT_H

#include "Camera.h"

//Нерисуемый, потому что только влияет на объекты сцены.
//Мы его не увидим, если не будет объектов сцены, отражающих его, верно?
class Light : public Camera
{
    friend class LightCaster;
public:
    Light() = default;
    Light(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward, const uint32_t& color);
    Light(const Camera& camera, const uint32_t& color);
    ~Light() override = default;

    glm::mat4x4 get_perspective_matrix() const;


    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

    float intensity = 1.0f;
    uint32_t color;
};

#include "Light.hpp"

#endif
