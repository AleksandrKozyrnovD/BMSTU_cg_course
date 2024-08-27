switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    glm::vec3 v = camera->forward * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);

                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    glm::vec3 v = -camera->forward * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    glm::vec3 v = -camera->right * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    camera = ControlSystem::SceneManager::get_main_camera();
                    camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                    glm::vec3 v = camera->right * 0.025f;
                    ControlSystem::DrawManager::do_we_draw = true;
                    ControlSystem::TransformManager::move(camera_obj, v.x, v.y, v.z);
                }
                //escape
                else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    this->cursor_controls = !this->cursor_controls;
                    SDL_ShowCursor(this->cursor_controls);
                }
                break;
            case SDL_MOUSEMOTION:
                if (this->cursor_controls)
                {
                    // std::cout << "Controls enabled" << std::endl;

                    dx = -event.motion.xrel;
                    dy = event.motion.yrel;
                    if (dx != 0 || dy != 0)
                    {
                        camera = ControlSystem::SceneManager::get_main_camera();
                        camera_obj = std::static_pointer_cast<AbstractObject>(camera);
                        ControlSystem::TransformManager::rotate_archaic(camera_obj, dy / 10.0f,-dx / 10.0f, 0.0f);
                        ControlSystem::DrawManager::do_we_draw = true;
                    }
                }
                break;

            default:
                break;
        }