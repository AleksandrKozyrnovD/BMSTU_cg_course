#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

namespace ControlSystem
{
    class BaseManager
    {
    public:
        BaseManager() = default;
        virtual ~BaseManager() = default;
    };
}

#include "TransformManager.h"
#include "LoadManager.h"
#include "SceneManager.h"
#include "DrawManager.h"

#endif
