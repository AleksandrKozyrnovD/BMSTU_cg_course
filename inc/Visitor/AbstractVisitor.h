#ifndef __ABSTRACT_VISITOR_H__
#define __ABSTRACT_VISITOR_H__

class CompositeObject;
class Model;
class Camera;


class AbstractVisitor
{
public:
    AbstractVisitor() = default;
    virtual ~AbstractVisitor() = default;

    virtual void visit(Model& obj) = 0;
    virtual void visit(Camera& obj) = 0;
    virtual void visit(CompositeObject& obj) = 0;
};



#endif