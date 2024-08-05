#ifndef __DRAW_VISITOR_H__
#define __DRAW_VISITOR_H__

#include "AbstractVisitor.h"
#include "Canvas.h"
#include "ModelType/Facet.h"
#include "Camera.h"

class DrawVisitor : public AbstractVisitor
{
public:
    DrawVisitor() = delete;
    explicit DrawVisitor(std::shared_ptr<Camera>& camera);
    ~DrawVisitor() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;

protected:
    std::shared_ptr<Camera>& camera;

private:
    void draw_facet(const Facet& facet);
    glm::mat4x4 transform;
};

#include "DrawVisitor.hpp"

#endif
