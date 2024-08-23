#ifndef __DRAW_VISITOR_H__
#define __DRAW_VISITOR_H__

#include "Drawer.h"


class DrawVisitor : public Drawer
{
public:
    DrawVisitor() = delete;
    explicit DrawVisitor(std::shared_ptr<Camera>& camera);
    ~DrawVisitor() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;

protected:
    uint32_t color;

    void process_facet(const Facet& facet) override;
    void process_scanline(float y, GLMSlope& A, GLMSlope& B) override;

};

#include "DrawVisitor.hpp"

#endif
