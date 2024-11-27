#include "CommandClasses/Scene/Interaction.h"
void ImguiInterface::draw_overlay()
{
    static int location = 3;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (location >= 0)
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    else if (location == -2)
    {
        // Center window
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    // bool p_open = true;
    if (ImGui::Begin("Example: Simple overlay", ImguiInterface::b_overlay, window_flags))
    {
        // IMGUI_DEMO_MARKER("Examples/Simple Overlay");
        ImGui::Text("Overlay\n");
        ImGui::Separator();
        if (ImGui::IsMousePosValid())
        {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);

            float x, y, z;
            auto command = Actions::Scene::GetWorldPosition(x, y, z, io.MousePos.x, io.MousePos.y);
            Facade::execute(&command);
            ImGui::Text("World Position: (%.1f,%.1f,%.1f)", x, y, z);


            float x1, y1, z1, x2, y2, z2, x3, y3, z3;
            auto command2 = Actions::Scene::GetCameraVectors(x1, y1, z1, x2, y2, z2, x3, y3, z3);
            Facade::execute(&command2);
            ImGui::Text("Camera Vectors:");
            ImGui::Text("fwd: (%.3f,%.3f,%.3f)", x1, y1, z1);
            ImGui::Text("rght: (%.3f,%.3f,%.3f)", x2, y2, z2);
            ImGui::Text("up: (%.3f,%.3f,%.3f)", x3, y3, z3);

            auto command3 = Actions::Scene::GetCameraPos(x, y, z);
            Facade::execute(&command3);
            ImGui::Text("Camera Position: (%.3f,%.3f,%.3f)", x, y, z);
        }
        else
            ImGui::Text("Mouse Position: <invalid>");
        // if (ImGui::BeginPopupContextWindow())
        // {
        //     if (ImGui::MenuItem("Custom",       NULL, location == -1)) location = -1;
        //     if (ImGui::MenuItem("Center",       NULL, location == -2)) location = -2;
        //     if (ImGui::MenuItem("Top-left",     NULL, location == 0)) location = 0;
        //     if (ImGui::MenuItem("Top-right",    NULL, location == 1)) location = 1;
        //     if (ImGui::MenuItem("Bottom-left",  NULL, location == 2)) location = 2;
        //     if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
        //     if (p_open && ImGui::MenuItem("Close")) *p_open = false;
        //     ImGui::EndPopup();
        // }
    }
    ImGui::End();
}