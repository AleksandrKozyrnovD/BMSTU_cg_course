#include "Buffer.inl"
#include "InteractionManager.h"
#include "SceneManager.h"

using namespace ControlSystem;

void InteractionManager::get_world_pos(float &mouse_x, float &mouse_y, float &z)
{
    auto camera = ControlSystem::SceneManager::get_main_camera();

    glm::mat4 view = camera->get_view_matrix();
    glm::mat4 projection = camera->get_perspective_matrix();

    glm::mat4 transform = projection * view;

    glm::vec4 viewport(0.0f, 0.0f, Buffer::width, Buffer::height);

    float z_tmp = Buffer::depth_buffer[mouse_y][mouse_x];

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