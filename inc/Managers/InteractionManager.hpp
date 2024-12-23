#include "Buffer.inl"
#include "DrawManager.h"
#include "InteractionManager.h"
#include "SceneManager.h"
#include "TransformManager.h"

using namespace ControlSystem;

void InteractionManager::get_world_pos(float &mouse_x, float &mouse_y, float &z)
{
    auto camera = ControlSystem::SceneManager::get_main_camera();

    glm::mat4 view = camera->get_view_matrix();
    glm::mat4 projection = camera->get_perspective_matrix();

    glm::mat4 transform = projection * view;

    glm::vec4 viewport(0.0f, 0.0f, Buffer::width, Buffer::height);

    float z_tmp;
    if (mouse_x > 0 && mouse_x < Buffer::width && mouse_y > 0 && mouse_y < Buffer::height)
        z_tmp = Buffer::depth_buffer[mouse_y][mouse_x];
    else
        z_tmp = 0.0f;

    glm::vec3 point(mouse_x, mouse_y, z_tmp);

    point = glm::unProject(point, view, projection, viewport);

    mouse_x = point.x;
    mouse_y = point.y;
    z = point.z;
}

void InteractionManager::get_camera_vectors(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2, float &x3, float &y3, float &z3)
{
    auto camera = ControlSystem::SceneManager::get_main_camera();

    x1 = camera->forward.x;
    y1 = camera->forward.y;
    z1 = camera->forward.z;

    x2 = camera->right.x;
    y2 = camera->right.y;
    z2 = camera->right.z;

    x3 = camera->up.x;
    y3 = camera->up.y;
    z3 = camera->up.z;
}

void InteractionManager::get_camera_position(float &x, float &y, float &z)
{
    auto camera = ControlSystem::SceneManager::get_main_camera();

    x = camera->get_center().x;
    y = camera->get_center().y;
    z = camera->get_center().z;
}


#include <glm/gtx/matrix_decompose.hpp>
void InteractionManager::get_object_translation(size_t id, float &x, float &y, float &z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(object->transform, scale, rotation, translation, skew,perspective);
    // rotation = glm::conjugate(rotation);

    x = translation.x;
    y = translation.y;
    z = translation.z;
}


void InteractionManager::get_object_rotation(size_t id, float &x, float &y, float &z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(object->transform, scale, rotation, translation, skew,perspective);
    rotation = glm::conjugate(rotation);

    x = rotation.x;
    y = rotation.y;
    z = rotation.z;
}

void InteractionManager::get_object_scale(size_t id, float &x, float &y, float &z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(object->transform, scale, rotation, translation, skew,perspective);
    // rotation = glm::conjugate(rotation);

    x = scale.x;
    y = scale.y;
    z = scale.z;
}

void InteractionManager::move_object(size_t id, float x, float y, float z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    ControlSystem::TransformManager::move(object, x, y, z);
    ControlSystem::DrawManager::do_we_draw = true;
}

void InteractionManager::rotate_object(size_t id, float x, float y, float z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    ControlSystem::TransformManager::rotate(object, x, y, z);
    ControlSystem::DrawManager::do_we_draw = true;
}

void InteractionManager::scale_object(size_t id, float x, float y, float z)
{
    auto object = ControlSystem::SceneManager::get_object(id);

    ControlSystem::TransformManager::scale(object, x, y, z);
    ControlSystem::DrawManager::do_we_draw = true;
}