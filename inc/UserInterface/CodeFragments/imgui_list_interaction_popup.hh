if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
                {
                    selected_list = n;
                    float x, y, z;
                    auto translation = Actions::Scene::GetObjectTranslation(id, x, y, z);
                    ControlSystem::Facade::execute(&translation);
                    ImGui::Text("Translation: (%.3f,%.3f,%.3f)", x, y, z);

                    auto rotation = Actions::Scene::GetObjectRotation(id, x, y, z);
                    ControlSystem::Facade::execute(&rotation);
                    ImGui::Text("Rotation: (%.3f,%.3f,%.3f)", x, y, z);

                    auto scale = Actions::Scene::GetObjectScale(id, x, y, z);
                    ControlSystem::Facade::execute(&scale);
                    ImGui::Text("Scale: (%.3f,%.3f,%.3f)", x, y, z);


                    // if (ImGui::Button("Move"))
                    static int dx = 0;
                    static int dy = 0;
                    static int dz = 0;
                    //on the same line
                    ImGui::InputInt("dx", &dx);
                    ImGui::SameLine();
                    ImGui::InputInt("dy", &dy);
                    ImGui::SameLine();
                    ImGui::InputInt("dz", &dz);
                    if (ImGui::Button("Move"))
                    {
                        Actions::Scene::MoveObjectScene move(id, dx, dy, dz);
                        ControlSystem::Facade::execute(&move);
                    }

                    static int rx = 0;
                    static int ry = 0;
                    static int rz = 0;
                    ImGui::InputInt("rx", &rx);
                    ImGui::SameLine();
                    ImGui::InputInt("ry", &ry);
                    ImGui::SameLine();
                    ImGui::InputInt("rz", &rz);
                    if (ImGui::Button("Rotate"))
                    {
                        Actions::Scene::RotateObjectScene rotate(id, rx, ry, rz);
                        ControlSystem::Facade::execute(&rotate);
                    }

                    static int sx = 1;
                    static int sy = 1;
                    static int sz = 1;
                    ImGui::InputInt("sx", &sx, 1);
                    ImGui::SameLine();
                    ImGui::InputInt("sy", &sy, 1);
                    ImGui::SameLine();
                    ImGui::InputInt("sz", &sz, 1);
                    if (sx < 1) sx = 1;
                    if (sy < 1) sy = 1;
                    if (sz < 1) sz = 1;
                    if (ImGui::Button("Scale"))
                    {
                        Actions::Scene::ScaleObjectScene scale(id, sx, sy, sz);
                        ControlSystem::Facade::execute(&scale);
                    }

                    if (ImGui::Button("Close"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }
                // ImGui::SetItemTooltip("Right-click to open popup");