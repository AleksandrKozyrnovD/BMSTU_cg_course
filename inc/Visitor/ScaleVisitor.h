#ifndef __SCALE_VISITOR_H__
#define __SCALE_VISITOR_H__

#include "TransformVisitor.h"

class ScaleVisitor : public TransformVisitor
{
public:
    ScaleVisitor() = default;
    ScaleVisitor(const ScaleVisitor& other) = default;
    ScaleVisitor(ScaleVisitor&& other) = default;
    ScaleVisitor(double x, double y, double z);
    ~ScaleVisitor() = default;


    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
};

#include "ScaleVisitor.hpp"


#endif