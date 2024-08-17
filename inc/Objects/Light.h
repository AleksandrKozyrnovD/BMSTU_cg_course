#ifndef __LIGHT_H
#define __LIGHT_H

#include "Camera.h"

//Нерисуемый, потому что только влияет на объекты сцены.
//Мы его не увидим, если не будет объектов сцены, отражающих его, верно?
class Light : public Camera
{
public:
    Light() = default;
    Light(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward, const glm::vec4& color);
    Light(const Camera& camera, const glm::vec4& color);
    ~Light() override = default;

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

protected:
    glm::vec4 color;
};

#include "Light.hpp"

#endif
