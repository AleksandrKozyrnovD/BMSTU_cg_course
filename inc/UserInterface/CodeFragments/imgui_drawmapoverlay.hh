#include "imgui.h"
void ImguiInterface::draw_map_overlay()
{
    // Calculate the dynamic cell size based on the total grid size
    auto& map = SceneManager::get_map();
    float totalGridSize = 150.0f;
    int gridSize = map.w;
    float cellSize = totalGridSize / gridSize;

    // Position overlay at the bottom-left corner
    ImGui::SetNextWindowPos(ImVec2(10, ImGui::GetIO().DisplaySize.y - totalGridSize - cellSize), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);  // Transparent background for the overlay

    // Start overlay window with no title bar, resizing, or moving
    ImGui::Begin("GridOverlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

    // Remove spacing and padding between items
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            // Unique ID for each cell to avoid ImGui conflicts
            ImGui::PushID(row * gridSize + col);

            // ImGui::PushStyleColor(ImGuiCol_Button, cellColors[cellIndex]);
            // ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(cellColors[cellIndex].x * 1.2f, cellColors[cellIndex].y * 1.2f, cellColors[cellIndex].z * 1.2f, 1.0f));
            // ImGui::PushStyleColor(ImGuiCol_ButtonActive, cellColors[cellIndex]);

            // Create a button for each cell
            if (ImGui::Button("##cell", ImVec2(cellSize, cellSize)))
            {
                // Open the context menu on right-click
                ImGui::OpenPopup("cell_context_menu");
            }

            // Draw text inside the button
            // ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() - cellSize / 2 + 10, ImGui::GetCursorPosY() - cellSize / 2 + 10)); // Center text
            // ImGui::TextUnformatted(cellTexts[cellIndex].c_str());

            // If the context menu is open, show options
            if (ImGui::BeginPopup("cell_context_menu"))
            {
                // Display the coordinates in the context menu
                ImGui::Text("Cell coordinates: (%d, %d)", row, col);
                ImGui::Separator();
                
                // Add menu items here
                if (ImGui::MenuItem("Option 1"))
                {
                    // Handle Option 1
                }
                if (ImGui::MenuItem("Option 2"))
                {
                    // Handle Option 2
                }
                
                ImGui::EndPopup();
            }

            ImGui::PopID();

            // Move to next cell or new line
            if (col < gridSize - 1)
                ImGui::SameLine();
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    ImGui::End();
}