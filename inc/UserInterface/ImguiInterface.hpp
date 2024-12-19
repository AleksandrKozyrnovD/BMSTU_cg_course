// #include "DrawManager.h"
#include "ImguiInterface.h"
// #include "LoadManager.h"
// #include "SceneManager.h"
#include "imgui.h"

ImGuiParams ImguiInterface::param = ImGuiParams();

void ImguiInterface::draw_interface()
{
    ImguiInterface::draw_mainwindow();
}

bool* ImguiInterface::b_mainwindow = new bool;
bool* ImguiInterface::b_main_menu = new bool;
bool* ImguiInterface::b_overlay = new bool;
bool *ImguiInterface::b_map_overlay = new bool;
bool *ImguiInterface::b_show_model_browser = new bool;
bool *ImguiInterface::b_map_grid = new bool;
bool *ImguiInterface::b_new_scene_input = new bool;
bool *ImguiInterface::b_open_scene = new bool;
bool *ImguiInterface::controls_allowed = new bool;
bool *ImguiInterface::b_help = new bool;

void ImguiInterface::init_interface()
{
    *ImguiInterface::b_mainwindow = true;
    *ImguiInterface::b_main_menu = true;
    *ImguiInterface::b_overlay = false;
    *ImguiInterface::b_map_overlay = false;
    *ImguiInterface::b_show_model_browser = false;
    *ImguiInterface::b_map_grid = false;
    *ImguiInterface::b_new_scene_input = false;
    *ImguiInterface::b_open_scene = false;
    *ImguiInterface::controls_allowed = true;
    *ImguiInterface::b_help = false;
}

void ImguiInterface::end_interface()
{
    delete ImguiInterface::b_mainwindow;
    delete ImguiInterface::b_main_menu;
    delete ImguiInterface::b_overlay;
    delete ImguiInterface::b_map_overlay;
    delete ImguiInterface::b_show_model_browser;
    delete ImguiInterface::b_map_grid;
    delete ImguiInterface::b_new_scene_input;
    delete ImguiInterface::b_open_scene;
    delete ImguiInterface::controls_allowed;
    delete ImguiInterface::b_help;
}


void ImguiInterface::draw_mainwindow()
{
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        /* Tutorial */
        // ImGui::ShowDemoWindow(b_mainwindow);

        /* Interface is here */
        if (*b_main_menu)   ImguiInterface::draw_menu();
        if (*b_overlay)     ImguiInterface::draw_overlay();
        if (*b_map_overlay) ImguiInterface::draw_map_overlay();
        if (*b_show_model_browser) show_model_browser();
        if (*b_map_grid)    ImguiInterface::draw_map_grid();
        if (*b_new_scene_input) show_new_scene_input();
        if (*b_open_scene) open_scene();
        if (*b_help)        help();

        ImGui::EndFrame();
}

#include "CodeFragments/imgui_drawmenu.hh"
#include "CodeFragments/imgui_drawoverlay.hh"
#include "CodeFragments/imgui_drawmapoverlay.hh"
#include "CodeFragments/imgui_modelbrowser.hh"
// #include "CodeFragments/imgui_newscene.hh"
// #include "CodeFragments/imgui_loadscene.hh"

void ImguiInterface::open_scene()
{
    static std::shared_ptr<AbstractObject> obj = nullptr;
    std::string directoryPath = "/home/aleksandr/Desktop/bmstu/Curse/CGNEW/scenes";
    static std::string selectedModel = "No model selected";

    if (ImGui::Begin("Scene Browser", ImguiInterface::b_open_scene))
    {  // Open window
        ImGui::Columns(2, "modelColumns");  // Create two columns
        
        // Left column for model entries
        ImGui::Text("Select a .scene file:");
        ImGui::Separator();
        
        // Scan directory for .model files
        for (const auto& entry : fs::directory_iterator(directoryPath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".scene")
            {
                std::string modelFile = entry.path().filename().string();
                // std::string modelFile = entry.path().string();

                if (ImGui::Selectable(modelFile.c_str(), selectedModel == modelFile))
                {
                    selectedModel = entry.path().string();
                }
            }
        }

        ImGui::NextColumn();  // Move to the next column

        if (ImGui::Button("Load"))
        {
            SceneManager::clear_scene();
            std::cout << "Adding <" << selectedModel << "> to the application..." << std::endl;
            ControlSystem::LoadManager::load_scene(selectedModel);
            ControlSystem::DrawManager::do_we_draw = true;

            *ImguiInterface::b_open_scene = false;
        }

        ImGui::Columns(1);  // Reset columns to 1
    }
    ImGui::End();  // Close the window
}

void ImguiInterface::show_new_scene_input()
{
    static int input_value = 1;
    static char stringinput[255] = "inputfilename";

    *ImguiInterface::controls_allowed = false;

    ImGui::Begin("Enter Integer Value", ImguiInterface::b_new_scene_input, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Please enter a size of a plot (NxN) and a scene name (without extension)");
    // ImGui::InputInt("##input", &input_value);
    ImGui::SliderInt("##input", &input_value, 1, 10);
    ImGui::InputText("##file", stringinput, sizeof(stringinput) - 6);

    ImGui::Separator();

    if (ImGui::Button("Accept"))
    {
        Map m(input_value);
        SceneManager::clear_scene();
        SceneManager::set_map(m);
        SceneManager::fill_map();
        *ImguiInterface::b_new_scene_input = false;
        ControlSystem::DrawManager::do_we_draw = true;
        *ImguiInterface::controls_allowed = true;
        std::string loadfile = "scenes/";
        loadfile += stringinput;
        loadfile += ".scene";
        SceneManager::load_file = loadfile;
        // FILE *file = fopen(cd);
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
    {
        *ImguiInterface::b_new_scene_input = false;
        *ImguiInterface::controls_allowed = true;
    }


    ImGui::End();
}


void ImguiInterface::help()
{
    ImGui::Begin("Help", ImguiInterface::b_help);
    ImGui::Text("For movement use WASD keys. For camera rotation use arrow keys.");
    ImGui::Text("Movement do not account for camera direction.");
    ImGui::End();
}