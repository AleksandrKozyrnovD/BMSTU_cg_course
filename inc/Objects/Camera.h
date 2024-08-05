#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Drawable.h"
// #include "Point.h"

#include "glm/mat4x4.hpp"

class Camera : public Undrawable
{
    friend class MoveVisitor;
    friend class RotateVisitor;
    friend class ScaleVisitor;
    friend class DrawVisitor;
public:
    Camera() = default;
    Camera(double x, double y, double z);
    Camera(const glm::vec3& center);
    Camera(const glm::vec3& center, const glm::vec3& up, const glm::vec3& forward);
    ~Camera() = default;


    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

    glm::mat4x4 get_view_matrix() const;

    glm::mat4x4 get_perspective_matrix() const;

public:
    // glm::vec3 center;

    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;

    float fov = 45;
};

#include "Camera.hpp"

#endif