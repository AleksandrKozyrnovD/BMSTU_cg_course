#ifndef __TRANSFORM_MANAGER_H__
#define __TRANSFORM_MANAGER_H__

#include "BaseManager.h"
#include "AbstractObject.h"

namespace ControlSystem
{
    using object_ptr = std::shared_ptr<AbstractObject>&;

    class TransformManager : public BaseManager
    {
    public:
        TransformManager() = delete;
        ~TransformManager();

        static void move(object_ptr obj, float x, float y, float z);
        static void scale(object_ptr obj, float x, float y, float z);
        static void rotate(object_ptr obj, float x, float y, float z);
        static void rotate_archaic(object_ptr obj, float x, float y, float z);
    };
}

#include "TransformManager.hpp"

#endif

