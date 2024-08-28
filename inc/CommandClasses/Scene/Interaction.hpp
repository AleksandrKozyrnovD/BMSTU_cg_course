#include "Interaction.h"
#include "InteractionManager.h"

using namespace Actions::Scene;


GetWorldPosition::GetWorldPosition(float &x, float &y, float &z, float mouse_x, float mouse_y)
    : x(x), y(y), z(z), mouse_x(mouse_x), mouse_y(mouse_y)
{
    this->method = ControlSystem::InteractionManager::get_world_pos;
}

void GetWorldPosition::Execute()
{
    (*method)(mouse_x, mouse_y, z);

    x = mouse_x;
    y = mouse_y;
}


GetCameraVectors::GetCameraVectors(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2, float &x3, float &y3, float &z3)
    : x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), x3(x3), y3(y3), z3(z3)
{
    this->method = ControlSystem::InteractionManager::get_camera_vectors;
}

void GetCameraVectors::Execute()
{
    (*method)(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}


GetCameraPos::GetCameraPos(float &x, float &y, float &z)
    : x(x), y(y), z(z)
{
    this->method = ControlSystem::InteractionManager::get_camera_position;
}

void GetCameraPos::Execute()
{
    (*method)(x, y, z);
}



GetObjectTranslation::GetObjectTranslation(size_t id, float &x, float &y, float &z)
    : x(x), y(y), z(z), id(id)
{
    this->method = ControlSystem::InteractionManager::get_object_translation;
}

void GetObjectTranslation::Execute()
{
    (*method)(id, x, y, z);
}


GetObjectScale::GetObjectScale(size_t id, float &x, float &y, float &z)
    : x(x), y(y), z(z), id(id)
{
    this->method = ControlSystem::InteractionManager::get_object_scale;
}

void GetObjectScale::Execute()
{
    (*method)(id, x, y, z);
}


GetObjectRotation::GetObjectRotation(size_t id, float &x, float &y, float &z)
    : x(x), y(y), z(z), id(id)
{
    this->method = ControlSystem::InteractionManager::get_object_rotation;
}

void GetObjectRotation::Execute()
{
    (*method)(id, x, y, z);
}

MoveObjectScene::MoveObjectScene(size_t id, float x, float y, float z)
    : id(id), x(x), y(y), z(z)
{
    this->method = ControlSystem::InteractionManager::move_object;
}

void MoveObjectScene::Execute()
{
    (*method)(id, x, y, z);
}

RotateObjectScene::RotateObjectScene(size_t id, float x, float y, float z)
    : id(id), x(x), y(y), z(z)
{
    this->method = ControlSystem::InteractionManager::rotate_object;
}

void RotateObjectScene::Execute()
{
    (*method)(id, x, y, z);
}

ScaleObjectScene::ScaleObjectScene(size_t id, float x, float y, float z)
    : id(id), x(x), y(y), z(z)
{
    this->method = ControlSystem::InteractionManager::scale_object;
}

void ScaleObjectScene::Execute()
{
    (*method)(id, x, y, z);
}

