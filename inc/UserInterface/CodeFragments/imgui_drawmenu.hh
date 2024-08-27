#include "CommandClasses/Scene/Interaction.h"
#include "DrawManager.h"
#include "Facade.h"
#include "LoadManager.h"
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
        Add Object
        Delete Object
        Rotate Object
        Move Object
        Scale Object
        list of objects
            - if clicked, show options
                - Delete
                - Rotate
                - Move
                - Scale
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
                ControlSystem::LoadManager::load_scene("/home/aleksandr/Desktop/bmstu/Curse/CGNEW/models/scene.txt");
                ControlSystem::DrawManager::do_we_draw = true;
            }

            if (ImGui::MenuItem("Save"))
            {
                ;
            }

            if (ImGui::MenuItem("Save As"))
            {
                ;
            }
            if (ImGui::MenuItem("New"))
            {
                ;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Add Object"))
            {
                ;
            }
            if (ImGui::MenuItem("Delete Object"))
            {
                ;
            }
            if (ImGui::MenuItem("Rotate Object"))
            {
                ;
            }
            if (ImGui::MenuItem("Move Object"))
            {
                ;
            }
            if (ImGui::MenuItem("Scale Object"))
            {
                ;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("List"))
        {
            // const char* names[5] = { "Label1", "Label2", "Label3", "Label4", "Label5" };
            // static int selected = -1;
            // for (int n = 0; n < 5; n++)
            // {
            //     if (ImGui::Selectable(names[n], selected == n))
            //         selected = n;
            //     if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
            //     {
            //         selected = n;
            //         ImGui::Text("This a popup for \"%s\"!", names[n]);
            //         if (ImGui::Button("Close"))
            //             ImGui::CloseCurrentPopup();
            //         ImGui::EndPopup();
            //     }
            //     ImGui::SetItemTooltip("Right-click to open popup");
            // }

            static int selected_list = -1;
            auto objects = ControlSystem::SceneManager::get_drawable_objects();
            for (int n = 0; n < objects.size(); n++)
            {
                size_t id = objects[n]->get_id();
                std::string name = "Object id: " + std::to_string(id);
                if (ImGui::Selectable(name.c_str(), selected_list == n))
                    selected_list = n;
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


                    ImGui::Text("This a popup for \"%s\"!", name.c_str());
                    if (ImGui::Button("Close"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }
                ImGui::SetItemTooltip("Right-click to open popup");
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Add Camera"))
            {
                ;
            }
            if (ImGui::MenuItem("Delete Camera"))
            {
                ;
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Main Camera Options"))
            {
                if (ImGui::MenuItem("Set Main Camera"))
                {
                    ;
                }
                if (ImGui::MenuItem("Change Main Camera"))
                {
                    ;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Options"))
        {
            ImGui::Checkbox("Enable overlay", ImguiInterface::b_overlay);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}