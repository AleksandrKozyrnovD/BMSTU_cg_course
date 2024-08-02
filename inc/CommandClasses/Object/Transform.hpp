#include "Transform.h"
#include "TransformManager.h"


Actions::Object::RotateArchaic::RotateArchaic(ControlSystem::object_ptr obj, float x, float y, float z)
    : obj(obj), x(x), y(y), z(z)
{
    this->method = &ControlSystem::TransformManager::rotate_archaic;
}

void Actions::Object::RotateArchaic::Execute()
{
    (*method)(obj, x, y, z);
}

Actions::Object::Rotate::Rotate(ControlSystem::object_ptr obj, float x, float y, float z)
    : obj(obj), x(x), y(y), z(z)
{
    this->method = &ControlSystem::TransformManager::rotate;
}

void Actions::Object::Rotate::Execute()
{
    (*method)(obj, x, y, z);
}



Actions::Object::Move::Move(ControlSystem::object_ptr obj, float x, float y, float z)
    : obj(obj), x(x), y(y), z(z)
{
    this->method = &ControlSystem::TransformManager::move;
}

void Actions::Object::Move::Execute()
{
    (*method)(obj, x, y, z);
}


Actions::Object::Scale::Scale(ControlSystem::object_ptr obj, float x, float y, float z)
    : obj(obj), x(x), y(y), z(z)
{
    this->method = &ControlSystem::TransformManager::scale;
}

void Actions::Object::Scale::Execute()
{
    (*method)(obj, x, y, z);
}