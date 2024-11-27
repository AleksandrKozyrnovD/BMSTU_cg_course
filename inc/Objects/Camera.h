#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Drawable.h"
// #include "Point.h"

#include "glm/mat4x4.hpp"

#include <iostream>

class Camera : public Undrawable
{
    friend class MoveVisitor;
    friend class RotateVisitor;
    friend class ScaleVisitor;
    friend class DrawVisitor;
public:
    Camera();
    Camera(double x, double y, double z);
    explicit Camera(const glm::vec3& center);
    Camera(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward);
    ~Camera() = default;


    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

    glm::mat4x4 get_view_matrix() const;

    glm::mat4x4 get_perspective_matrix() const;

public:
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;

    float fov = 90;
};



class CameraV2 : public Camera
{
public:
    glm::vec3 position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    CameraV2(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& proj)
        : position(pos), viewMatrix(view), projectionMatrix(proj) {}

    CameraV2(const glm::vec3& up, const glm::vec3& right, const glm::vec3& forward, const glm::vec3& pos)
        : Camera(center, up, forward), position(pos)
    {
        viewMatrix = glm::mat4(
            glm::vec4(right, 0.0f),
            glm::vec4(up, 0.0f),
            glm::vec4(-forward, 0.0f),
            glm::vec4(pos, 1.0f)
        );
        viewMatrix = glm::inverse(viewMatrix);
    }

    glm::vec3 project(const glm::vec3& point) const
    {
        // Перевод точки в координаты clip-space
        glm::vec4 clipSpace = projectionMatrix * viewMatrix * glm::vec4(point, 1.0f);

        // std::cout << "Clipspace: " << clipSpace.x << " " << clipSpace.y << " " << clipSpace.z << " " << clipSpace.w << std::endl;

        // Если w = 0, точка на плоскости проекции недопустима
        if (clipSpace.w == 0) {
            return glm::vec3(0.0f, 0.0f, 1.0f); // Считаем точку невидимой
        }

        // Нормализация по w
        clipSpace /= clipSpace.w;

        // Преобразование в экранные координаты (от 0 до 1)
        float x = (clipSpace.x + 1.0f) * 0.5f;
        float y = (clipSpace.y + 1.0f) * 0.5f;
        float z = clipSpace.z; // z в диапазоне [-1, 1]

        return glm::vec3(x, y, z);
    }
};

#include "Camera.hpp"

#endif