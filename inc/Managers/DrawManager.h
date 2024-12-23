#ifndef __DRAW_MANAGER_H__
#define __DRAW_MANAGER_H__

#include "BaseManager.h"
#include "Light.h"
#include "Application.h"

#include <memory>


namespace ControlSystem
{
    class DrawManager : public BaseManager
    {
    public:
        DrawManager() = delete;
        ~DrawManager() = default;

        static void set_window_size(int w, int h, Window::Settings& settings);

        static void draw_scene_no_lights();

        static void draw_scene();

        static void new_draw_scene();

        static bool do_we_draw;
    
    private:
        static void process_from_viewpoint(std::shared_ptr<Light>& light_sorce, std::shared_ptr<Camera>& camera, glm::mat4 transform);
    };
}

#include "DrawManager.hpp"


#endif
