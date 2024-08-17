#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "AbstractVisitor.h"
#include "Slope.h"

#include "Camera.h"
#include "ModelType/Facet.h"

class Drawer : public AbstractVisitor
{
public:
    virtual ~Drawer() = default;
    explicit Drawer(std::shared_ptr<Camera>& camera);

protected:
    std::shared_ptr<Camera>& camera;
    glm::mat4x4 transform;

    void process_facet(const Facet& facet); //depth + color

    virtual void process_scanline(float y, GLMSlope& A, GLMSlope& B) = 0;
};



#include "Drawer.hpp"

#endif
