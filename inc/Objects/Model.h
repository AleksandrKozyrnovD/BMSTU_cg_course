#ifndef __MODEL_H__
#define __MODEL_H__

#include "Drawable.h"
#include "ModelType/AbstractSurfaceModel.h"


class Model : public Drawable
{
    friend class MoveVisitor;
    friend class RotateVisitor;
    friend class ScaleVisitor;
    friend class DrawVisitor;
    friend class DrawVisitor;
public:
    Model() = default;
    Model(const Model& other) = default;
    explicit Model(const std::shared_ptr<AbstractSurfaceModel>& model) noexcept;

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;


protected:
    std::shared_ptr<AbstractSurfaceModel> model;
};

#include "Model.hpp"


#endif