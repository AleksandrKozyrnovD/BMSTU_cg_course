#ifndef __INTERACTION_MANAGER_H__
#define __INTERACTION_MANAGER_H__

#include "BaseManager.h"

namespace ControlSystem
{
    class InteractionManager : public BaseManager
    {
    public:
        InteractionManager() = delete;
        ~InteractionManager() = default;


        static void get_world_pos(float &mouse_x, float &mouse_y, float &z);

        static void get_camera_vectors(float &x1, float &y1, float &z1,
                                      float &x2, float &y2, float &z2,
                                      float &x3, float &y3, float &z3);

    };
}

#include "InteractionManager.hpp"

#endif
