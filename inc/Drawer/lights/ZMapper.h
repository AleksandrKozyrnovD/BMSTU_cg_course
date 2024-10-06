#ifndef __Z_MAPPER_H__
#define __Z_MAPPER_H__

#include "Drawer.h"

#include "Camera.h"


class ZMapper : public Drawer
{
public:
    ZMapper() = delete;
    explicit ZMapper(std::shared_ptr<Camera>& camera);
    ~ZMapper() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;   

protected:
    virtual void process_facet(const Facet& facet) override;
    virtual void process_scanline(float y, GLMSlope& A, GLMSlope& B) override;
};

#include "ZMapper.hpp"

#endif