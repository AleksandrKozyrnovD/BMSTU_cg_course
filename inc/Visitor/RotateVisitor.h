#ifndef __ROTATE_VISITOR_H__
#define __ROTATE_VISITOR_H__

#include "TransformVisitor.h"

class RotateVisitor : public TransformVisitor
{
public:
    RotateVisitor() = default;
    RotateVisitor(const RotateVisitor& other) = default;
    RotateVisitor(RotateVisitor&& other) = default;
    RotateVisitor(double x, double y, double z);
    ~RotateVisitor() = default;


    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;
};

#include "RotateVisitor.hpp"


#endif