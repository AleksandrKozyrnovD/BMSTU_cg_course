#include "AbstractVisitor.h"
#include "TransformManager.h"
#include "TransformVisitor.h"
#include <memory>


void ControlSystem::TransformManager::move(object_ptr obj, float x, float y, float z)
{
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<MoveVisitor>(x, y, z);
    obj->accept(visitor);
}

void ControlSystem::TransformManager::scale(object_ptr obj, float x, float y, float z)
{
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<ScaleVisitor>(x, y, z);
    obj->accept(visitor);
}

void ControlSystem::TransformManager::rotate(object_ptr obj, float x, float y, float z)
{
    glm::vec3 center = obj->get_center();

    std::shared_ptr<AbstractVisitor> move_to_center = std::make_shared<MoveVisitor>(-center.x, -center.y, -center.z);
    obj->accept(move_to_center);

    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<RotateVisitor>(x, y, z);
    obj->accept(visitor);

    std::shared_ptr<AbstractVisitor> move_back = std::make_shared<MoveVisitor>(center.x, center.y, center.z);
    obj->accept(move_back);
}

void ControlSystem::TransformManager::rotate_archaic(object_ptr obj, float x, float y, float z)
{
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<RotateVisitor>(x, y, z);
    obj->accept(visitor);
}
