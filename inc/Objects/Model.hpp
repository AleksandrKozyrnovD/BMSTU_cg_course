#include "Model.h"


Model::Model(const std::shared_ptr<AbstractSurfaceModel>& model) noexcept
    : model(model)
{
    this->center = model->get_center();
}


void Model::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}