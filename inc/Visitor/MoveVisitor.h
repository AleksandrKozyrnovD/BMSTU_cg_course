#ifndef __MOVE_VISITOR_H__
#define __MOVE_VISITOR_H__

#include "TransformVisitor.h"

class MoveVisitor : public TransformVisitor
{
public:
    MoveVisitor() = default;
    MoveVisitor(const MoveVisitor& other) = default;
    MoveVisitor(MoveVisitor&& other) = default;
    MoveVisitor(double x, double y, double z);
    ~MoveVisitor() = default;


    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
    void visit(Light& obj) override;
};

#include "MoveVisitor.hpp"


#endif