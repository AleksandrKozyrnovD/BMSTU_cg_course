#ifndef __TRANSFORM_VISITOR_H__
#define __TRANSFORM_VISITOR_H__

#include "AbstractVisitor.h"
#include "../glm/glm/vec3.hpp"

class TransformVisitor : public AbstractVisitor
{
public:
    TransformVisitor() = default;
    TransformVisitor(double x, double y, double z) : coordinate(x, y, z) {}
protected:
    glm::vec3 coordinate;
};


#include "MoveVisitor.h"
#include "ScaleVisitor.h"
#include "RotateVisitor.h"

#endif