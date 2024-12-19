#include "DrawManager.h"
#include "Facade.h"
#include "imgui.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

void ImguiInterface::show_model_browser()
{
    static std::shared_ptr<AbstractObject> obj = nullptr;
    std::string directoryPath = "/home/aleksandr/Desktop/bmstu/Curse/CGNEW/models";
    static std::string selectedModel = "No model selected";
    static std::string descriptionContent = "No description available";


    if (ImGui::Begin("Model Browser", ImguiInterface::b_show_model_browser))
    {  // Open window
        ImGui::Columns(2, "modelColumns");  // Create two columns
        
        // Left column for model entries
        ImGui::Text("Select a .model file:");
        ImGui::Separator();
        
        // Scan directory for .model files
        for (const auto& entry : fs::directory_iterator(directoryPath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".txt")
            {
                std::string modelFile = entry.path().filename().string();
                // std::string modelFile = entry.path().string();

                if (ImGui::Selectable(modelFile.c_str(), selectedModel == modelFile))
                {
                    // On selection, set this model as selected
                    // selectedModel = modelFile;
                    selectedModel = entry.path().string();

                    // Try to open corresponding .descr file
                    // std::string descrPath = entry.path().replace_extension(".descr").string();
                    std::string descrPath = entry.path().string();
                    descrPath = descrPath.substr(0, descrPath.length() - 4) + ".descr";
                    std::ifstream descrFile(descrPath);

                    if (descrFile.is_open())
                    {
                        // Read description content
                        descriptionContent.assign((std::istreambuf_iterator<char>(descrFile)),
                                                  std::istreambuf_iterator<char>());
                        descrFile.close();
                    }
                    else
                    {
                        descriptionContent = "No description available.";
                    }
                }
            }
        }

        ImGui::NextColumn();  // Move to the next column

        // Right column for description
        ImGui::Text("Description:");
        ImGui::Separator();
        ImGui::TextWrapped("%s", descriptionContent.c_str());

        if (ImGui::Button("Add"))
        {
            std::cout << "Adding <" << selectedModel << "> to the application..." << std::endl;
            // obj = ControlSystem::LoadManager::load_from_file<SurfaceBuilder>(selectedModel);
            obj = ControlSystem::LoadManager::load_composite_object(selectedModel);
            std::cout << "Coordinates: (" << param.xi << ", " << param.yi << ")" << std::endl;

            if (obj != nullptr)
            {
                ControlSystem::TransformManager::move(obj, param.xi * 1.0f, 0.5f, param.yi * 1.0f);
                ControlSystem::SceneManager::add_object(obj);
                auto& map = SceneManager::get_map();
                map.map[param.xi][param.yi].object = obj;
                map.map[param.xi][param.yi].empty = false;
                ControlSystem::DrawManager::do_we_draw = true;
            }

            *ImguiInterface::b_show_model_browser = false;
        }

        ImGui::Columns(1);  // Reset columns to 1
    }
    ImGui::End();  // Close the window
}


// Function to show the grid
void ImguiInterface::draw_map_grid()
{

    static bool moveflag = false;
    auto& map = SceneManager::get_map();
    float totalGridSize = 450.0f;
    int gridSize = map.w;
    float cellSize = totalGridSize / gridSize;
   // Set ImGui window flags to make it non-resizable
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollbar
    | ImGuiWindowFlags_AlwaysAutoResize;

    // Open the grid window with specified flags
    // ImGui::SetNextWindowSize(ImVec2(totalGridSize * 1.0375f, totalGridSize * 1.0375f), ImGuiCond_Always);  // Set fixed size for the grid window
    
    ImGui::Begin("Grid", ImguiInterface::b_map_grid, windowFlags);  // Open the grid window
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3, 3));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

   for (int row = 0; row < gridSize; ++row)
   {
        for (int col = 0; col < gridSize; ++col)
        {
            // Unique ID for each cell to avoid ImGui conflicts
            ImGui::PushID(row * gridSize + col);

            if (map.map[row][col])
            {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0,0,255,255));
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0,255,0,255));
            }

            // Create a button for each cell
            if (ImGui::Button("##cell", ImVec2(cellSize, cellSize)))
            {
                if (moveflag)
                {
                    moveflag = false;
                    if (map.map[row][col])
                    {
                        std::cout << "Object already exists at (" << row << ", " << col << ")" << std::endl;
                    }
                    else
                    {
                        map.map[row][col].object = map.map[param.xi][param.yi].object;
                        map.map[row][col].empty = false;

                        map.map[param.xi][param.yi].object = nullptr;
                        map.map[param.xi][param.yi].empty = true;
                        
                        ControlSystem::DrawManager::do_we_draw = true;

                        auto difrow = row - param.xi;
                        auto difcol = col - param.yi;

                        ControlSystem::TransformManager::move(map.map[row][col].object, difrow * 1.0f, 0.0f, difcol * 1.0f);

                        std::cout << "Object moved from (" << param.xi << ", " << param.yi << ") to (" << row << ", " << col << ")" << std::endl;
                    }
                }
                else
                {
                    ImGui::OpenPopup("cell_context_menu");
                }
                // Open the context menu on right-click
            }

            // Unique popup name for each cell
            // std::string popupName = "cell_context_menu_" + std::to_string(row) + "_" + std::to_string(col);

            // If the context menu is open, show options
            // if (ImGui::BeginPopup(popupName.c_str()))
            if (ImGui::BeginPopup("cell_context_menu"))
            {
                // Display the coordinates in the context menu
                ImGui::Text("Cell coordinates: (%d, %d)", row, col);
                ImGui::Separator();

                // Add menu items here
                if (ImGui::MenuItem("Add")) {
                    // Handle Option 1
                    std::cout << "Option 1 selected at cell (" << row << ", " << col << ")" << std::endl;

                    if (map.map[row][col])
                    {
                        std::cout << "Object already exists at (" << row << ", " << col << ")" << std::endl;
                    }
                    else
                    {
                        ImguiInterface::param.xi = row;
                        ImguiInterface::param.yi = col;

                        *ImguiInterface::b_show_model_browser = true;
                        *ImguiInterface::b_map_grid = false;
                    }
                }
                if (ImGui::MenuItem("Delete")) {
                    // Handle Option 2
                    std::cout << "Option 2 selected at cell (" << row << ", " << col << ")" << std::endl;

                    if (map.map[row][col])
                    {
                        auto id = map.map[row][col].object->get_id();
                        ControlSystem::SceneManager::remove_object(id);
                        map.map[row][col].object = nullptr;
                        map.map[row][col].empty = true;
                        ControlSystem::DrawManager::do_we_draw = true;
                    }
                    else
                    {
                        std::cout << "Object does not exist at (" << row << ", " << col << ")" << std::endl;
                    }
                    *ImguiInterface::b_map_grid = false;
                }
                if (ImGui::MenuItem("Move"))
                {
                    std::cout << "Option 3 selected at cell (" << row << ", " << col << ")" << std::endl;

                    if (map.map[row][col])
                    {
                        moveflag = true;
                        ImguiInterface::param.xi = row;
                        ImguiInterface::param.yi = col;
                    }
                    else
                    {
                        std::cout << "No object exists at (" << row << ", " << col << ")" << std::endl;
                        *ImguiInterface::b_map_grid = false;
                    }
                }
                if (ImGui::MenuItem("Rotate clockwise"))
                {
                    std::cout << "Option 4 selected at cell (" << row << ", " << col << ")" << std::endl;

                    if (map.map[row][col])
                    {
                        auto& obj = map.map[row][col].object;
                        ControlSystem::TransformManager::rotate(obj, 0.0f, -90.0f, 0.0f);
                        DrawManager::do_we_draw = true;
                    }
                }
                if (ImGui::MenuItem("Rotate anticlockwise"))
                {
                    std::cout << "Option 5 selected at cell (" << row << ", " << col << ")" << std::endl;

                    if (map.map[row][col])
                    {
                        auto& obj = map.map[row][col].object;
                        ControlSystem::TransformManager::rotate(obj, 0.0f, 90.0f, 0.0f);
                        DrawManager::do_we_draw = true;
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::PopStyleColor();
            ImGui::PopID();

            // Move to next cell or new line
            if (col < gridSize - 1)
                ImGui::SameLine();
        }
    }

    ImGui::PopStyleVar(2);
    ImGui::End();
}