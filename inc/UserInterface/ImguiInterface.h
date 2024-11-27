#ifndef __IMGUI_INTERFACE_H__
#define __IMGUI_INTERFACE_H__

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>


#include "Facade.h" /* What really performs derictives to program thru input of something */

struct ImGuiParams
{
public:
    ImGuiParams() = default;
    ~ImGuiParams() = default;

public:
    int xi, yi, zi;
    int xi2, yi2, zi2;
    float xf, yf, zf;
    std::string in, out;
};

class ImguiInterface
{
public:
    ImguiInterface() = delete;
    ~ImguiInterface() = default;

    static void init_interface();
    static void draw_interface();
    static void end_interface();

private:
    static ImGuiParams param;
private:
    static void draw_mainwindow();      static bool *b_mainwindow;
    static void draw_menu();            static bool *b_main_menu;
    static void draw_overlay();         static bool *b_overlay;
    static void draw_map_overlay();     static bool *b_map_overlay;
    static void draw_map_grid();        static bool *b_map_grid;
    static void show_model_browser();   static bool *b_show_model_browser;
};

#include "ImguiInterface.hpp"

#endif

