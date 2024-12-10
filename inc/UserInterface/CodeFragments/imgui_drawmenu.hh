#include "CommandClasses/Scene/Interaction.h"
#include "DrawManager.h"
#include "Facade.h"
#include "ImGuiFileDialog.h"
#include "ImguiInterface.h"
#include "LoadManager.h"
#include "SceneManager.h"
#include "imgui.h"




void ImguiInterface::draw_menu()
{
    /*
    Scene:
        Open
        Save
        Save As
        New
    Edit:
        Open editor
    List:
        objects....
    View:
        Add Camera
        Delete Camera
        Main Camera Options:
            Set Main Camera
            Change Main Camera (fov, near, far)
    Options:
        Turn off/on overlay
    */
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Open"))
            {
                *ImguiInterface::b_open_scene = true;
            }

            if (ImGui::MenuItem("Save"))
            {
                // SceneManager::save_scene();
                std::cout << "Savefile = " << SceneManager::load_file << std::endl;
                if (SceneManager::load_file == "")
                {
                    return;
                }

                static float dx, dy, dz;
                static float rx, ry, rz;
                static float sx, sy, sz;
                

                static FILE *file = fopen(SceneManager::load_file.c_str(), "w");

                fprintf(file, "map 4 %zu 0 0 0 0 0 1 1 1\n", SceneManager::get_map_size());

                for (auto& obj : SceneManager::get_drawable_objects())
                {
                    if (obj->show) //only interactable(?) objects
                    {
                        auto translation = Actions::Scene::GetObjectTranslation(obj->get_id(), dx, dy, dz);
                        auto rotation = Actions::Scene::GetObjectRotation(obj->get_id(), rx, ry, rz);
                        auto scale = Actions::Scene::GetObjectScale(obj->get_id(), sx, sy, sz);

                        ControlSystem::Facade::execute(&translation);
                        ControlSystem::Facade::execute(&rotation);
                        ControlSystem::Facade::execute(&scale);
                        if (obj->IsComposite())
                        {
                            fprintf(file,"%s %d %f %f %f %f %f %f %f %f %f\n",
                                obj->load_file.c_str(), 3,
                                dx, dy, dz,
                                rx, ry, rz,
                                sx, sy, sz);
                        }
                        else
                        {
                            fprintf(file,"%s %d %f %f %f %f %f %f %f %f %f\n",
                                obj->load_file.c_str(), 1,
                                dx, dy, dz,
                                rx, ry, rz,
                                sx, sy, sz);
                        }
                    }
                }

                fclose(file);
            }
            // if (ImGui::MenuItem("Save As"))
            // {
            //     ;
            // }
            if (ImGui::MenuItem("New"))
            {
                *ImguiInterface::b_new_scene_input = true;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Open Editor"))
            {
                // *ImguiInterface::b_show_model_browser = true;
                *ImguiInterface::b_map_grid = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug List"))
        {
            static int selected_list = -1;
            auto objects = ControlSystem::SceneManager::get_drawable_objects();
            auto lights = ControlSystem::SceneManager::get_lights();
            auto cameras = ControlSystem::SceneManager::get_cameras();
            for (int n = 0; n < objects.size(); n++)
            {
                if (!objects[n]->show)
                {
                    continue;
                }
                size_t id = objects[n]->get_id();
                std::string name = "Object id: " + std::to_string(id);
                if (ImGui::Selectable(name.c_str(), selected_list == n))
                    selected_list = n;

                #include "CodeFragments/imgui_list_interaction_popup.hh"
            }
            ImGui::Separator();
            for (int n = 0; n < lights.size(); n++)
            {
                size_t id = lights[n]->get_id();
                std::string name = "Light id: " + std::to_string(id);
                if (ImGui::Selectable(name.c_str(), selected_list == n))
                    selected_list = n;

                #include "CodeFragments/imgui_list_interaction_popup.hh"
            }
            ImGui::Separator();
            for (int n = 0; n < cameras.size(); n++)
            {
                size_t id = cameras[n]->get_id();
                std::string name = "Camera id: " + std::to_string(id);
                if (ImGui::Selectable(name.c_str(), selected_list == n))
                    selected_list = n;

                #include "CodeFragments/imgui_list_interaction_popup.hh"
            }

            ImGui::EndMenu();
        }
        // if (ImGui::BeginMenu("View"))
        // {
        //     if (ImGui::MenuItem("Add Camera"))
        //     {
        //         ;
        //     }
        //     if (ImGui::MenuItem("Delete Camera"))
        //     {
        //         ;
        //     }
        //     ImGui::Separator();
        //     if (ImGui::BeginMenu("Main Camera Options"))
        //     {
        //         if (ImGui::MenuItem("Set Main Camera"))
        //         {
        //             ;
        //         }
        //         if (ImGui::MenuItem("Change Main Camera"))
        //         {
        //             ;
        //         }
        //         ImGui::EndMenu();
        //     }
        //     ImGui::EndMenu();
        // }
        if (ImGui::BeginMenu("Options"))
        {
            ImGui::Checkbox("Enable overlay", ImguiInterface::b_overlay);
            ImGui::Checkbox("Enable map overlay", ImguiInterface::b_map_overlay);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}