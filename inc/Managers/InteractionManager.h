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
        
        /*==========================================================================*/

        static void get_camera_position(float &x, float &y, float &z);

        static void get_object_translation(size_t id, float &x, float &y, float &z);

        static void get_object_rotation(size_t id, float &x, float &y, float &z);

        static void get_object_scale(size_t id, float &x, float &y, float &z);

        /*==========================================================================*/
        /* Actions that have rules, for example rotating strictly by 45 degrees, etc*/
        /* For now it simply placeholder functions */

        static void move_object(size_t id, float x, float y, float z);

        static void rotate_object(size_t id, float x, float y, float z);

        static void scale_object(size_t id, float x, float y, float z);
    };
}

#include "InteractionManager.hpp"

#endif
