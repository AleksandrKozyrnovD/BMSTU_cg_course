#include "Camera.h"
#include <SDL_scancode.h>
switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    // glm::vec3 v = camera->forward * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::TransformManager::move(camera_obj, 1.0f, 0.0f, 0.0f);

                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    // glm::vec3 v = -camera->forward * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    // ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                    ControlSystem::TransformManager::move(camera_obj, -1.0f, 0.0f, 0.0f);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    // glm::vec3 v = -camera->right * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    // ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                    ControlSystem::TransformManager::move(camera_obj, 0.0f, 0.0f, -1.0f);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    // glm::vec3 v = camera->right * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    // ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                    ControlSystem::TransformManager::move(camera_obj, 0.0f, 0.0f, 1.0f);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    ControlSystem::TransformManager::rotate(camera_obj, 0.0f, 15.0f, 0.0f);
                    ControlSystem::DrawManager::do_we_draw = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    ControlSystem::TransformManager::rotate(camera_obj, 0.0f, -15.0f, 0.0f);
                    ControlSystem::DrawManager::do_we_draw = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    ControlSystem::TransformManager::rotate(camera_obj, -15.0f, 0.0f, 0.0f);
                    ControlSystem::DrawManager::do_we_draw = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    ControlSystem::TransformManager::rotate(camera_obj, 15.0f, 0.0f, 0.0f);
                    ControlSystem::DrawManager::do_we_draw = true;
                }
                break;
            default:
                break;
        }