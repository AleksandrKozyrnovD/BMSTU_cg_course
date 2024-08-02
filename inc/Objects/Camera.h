#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Drawable.h"
#include "../BasicGraphic/Point.h"
#include "Vector.h"

class Camera : public Undrawable
{
    friend class MoveVisitor;
    friend class RotateVisitor;
    friend class ScaleVisitor;
    friend class DrawVisitor;
public:
    Camera() = default;
    Camera(double x, double y, double z);
    Camera(const Point& center);
    Camera(const Point& center, const Vector& up, const Vector& forward);
    ~Camera() = default;


    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

public:
    // Point center;

    Vector up;
    Vector forward;
    Vector right;
};

#include "Camera.hpp"

#endif