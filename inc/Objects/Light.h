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

    std::vector<std::vector<double>> shadow_buffer;

    void clear_shadow_buffer()
    {
        for (int i = 0; i < shadow_buffer.size(); ++i)
        {
            for (int j = 0; j < shadow_buffer[0].size(); ++j)
            {
                shadow_buffer[i][j] = 0.0f;
            }
        }
    }

    glm::mat4x4 get_rotation_matrix() const
    {
        glm::mat4x4 res = glm::mat4x4(1.0f);

        res[0] = glm::vec4(this->right, 0.0f);
        res[1] = glm::vec4(this->up, 0.0f);
        res[2] = glm::vec4(this->forward, 0.0f);

        res[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        return res;
    }
};


class LightV2 : public Light
{
public:
    glm::vec3 position;
    glm::vec3 color;

    LightV2(const glm::vec3& pos, const glm::vec3& col) : position(pos), color(col) {}
};

#include "Light.hpp"

#endif
