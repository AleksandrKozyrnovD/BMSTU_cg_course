#ifndef __IMGUI_INTERFACE_H__
#define __IMGUI_INTERFACE_H__

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>


#include "Facade.h" /* What really gives derictives to program thru input of something */

class ImguiInterface
{
public:
    ImguiInterface() = delete;
    ~ImguiInterface() = default;

    static void draw_interface();

private:
    static void draw_mainwindow(); static bool b_mainwindow;
};

#include "ImguiInterface.hpp"

#endif

