#include "Facade.h"
#include "ImguiInterface.h"
#include "imgui.h"

void ImguiInterface::draw_interface()
{
    ImguiInterface::draw_mainwindow();
}

bool* ImguiInterface::b_mainwindow = new bool;
bool* ImguiInterface::b_main_menu = new bool;
bool* ImguiInterface::b_overlay = new bool;

void ImguiInterface::init_interface()
{
    *ImguiInterface::b_mainwindow = true;
    *ImguiInterface::b_main_menu = true;
    *ImguiInterface::b_overlay = true;
}

void ImguiInterface::end_interface()
{
    delete ImguiInterface::b_mainwindow;
    delete ImguiInterface::b_main_menu;
    delete ImguiInterface::b_overlay;
}


void ImguiInterface::draw_mainwindow()
{
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        /* Tutorial */
        ImGui::ShowDemoWindow(b_mainwindow);

        /* Interface is here */
        if (*b_main_menu)   ImguiInterface::draw_menu();
        if (*b_overlay)     ImguiInterface::draw_overlay();



        ImGui::EndFrame();
}

#include "CodeFragments/imgui_drawmenu.hh"

#include "CodeFragments/imgui_drawoverlay.hh"