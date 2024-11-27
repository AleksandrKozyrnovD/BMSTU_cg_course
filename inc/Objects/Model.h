#ifndef __MODEL_H__
#define __MODEL_H__

#include "Drawable.h"
#include "ModelType/AbstractSurfaceModel.h"
// #include "normalzbuffer/NewDrawVisitor.h"


class Model : public Drawable
{
    friend class MoveVisitor;
    friend class RotateVisitor;
    friend class ScaleVisitor;
    friend class DrawVisitor;
    friend class Drawer;
    friend class ZMapper;
    friend class LightCaster;
    friend class NewDrawVisitor;
    friend class ShadowMapper;
    friend class ZBufMapper;
    friend class Scene;

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