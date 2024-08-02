#ifndef __OBJECT_TRANSFORM_H__
#define __OBJECT_TRANSFORM_H__


#include "CommandClasses/BaseCommand.h"

#include "TransformManager.h"

namespace Actions
{
    namespace Object
    {
        class RotateArchaic : public BaseCommand
        {
        using Action = void (*)(ControlSystem::object_ptr obj, float, float, float);
        public:
            RotateArchaic() = delete;
            RotateArchaic(ControlSystem::object_ptr obj, float x, float y, float z);
            ~RotateArchaic() = default;

            void Execute() override;

        private:
            Action method;
            ControlSystem::object_ptr obj;
            float x, y, z;
        };

        class Rotate : public BaseCommand
        {
        using Action = void (*)(ControlSystem::object_ptr obj, float, float, float);
        public:
            Rotate() = delete;
            Rotate(ControlSystem::object_ptr obj, float x, float y, float z);
            ~Rotate() = default;

            void Execute() override;

        private:
            Action method;
            ControlSystem::object_ptr obj;
            float x, y, z;
        };

        class Move : public BaseCommand
        {
        using Action = void (*)(ControlSystem::object_ptr obj, float, float, float);
        public:
            Move() = delete;
            Move(ControlSystem::object_ptr obj, float x, float y, float z);
            ~Move() = default;

            void Execute() override;

        private:
            Action method;
            ControlSystem::object_ptr obj;
            float x, y, z;
        };

        class Scale : public BaseCommand
        {
        using Action = void (*)(ControlSystem::object_ptr obj, float, float, float);
        public:
            Scale() = delete;
            Scale(ControlSystem::object_ptr obj, float x, float y, float z);
            ~Scale() = default;

            void Execute() override;

        private:
            Action method;
            ControlSystem::object_ptr obj;
            float x, y, z;
        };
    }
}

#include "Transform.hpp"

#endif
