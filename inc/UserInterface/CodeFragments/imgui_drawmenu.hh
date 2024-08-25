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
    View:
        Add Camera
        Delete Camera
        Main Camera Options:
            Set Main Camera
            Change Main Camera
    Options:
        None at the moment
    */
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Open"))
            {
                ;
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