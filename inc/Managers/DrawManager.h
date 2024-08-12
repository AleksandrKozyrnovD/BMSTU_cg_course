#ifndef __DRAW_MANAGER_H__
#define __DRAW_MANAGER_H__

#include "BaseManager.h"
#include "Color.h"


#include <vector>


namespace ControlSystem
{
    class DrawManager : public BaseManager
    {
    public:
        DrawManager() = delete;
        ~DrawManager() = default;

        static void set_window_size(int w, int h);

        static void draw_scene_no_lights();

        static void draw_scene();
    };
}

#include "Buffer.inl"
#include "DrawManager.hpp"


#endif
