#ifndef __SCENE_INTERACTION_H__
#define __SCENE_INTERACTION_H__

#include "AbstractObject.h"
#include "CommandClasses/BaseCommand.h"
#include <memory>


namespace Actions
{
    namespace Scene
    {
        class GetWorldPosition : public BaseCommand
        {
        using Action = void (*)(float &, float &, float &);
        public:
            GetWorldPosition() = delete;
            explicit GetWorldPosition(float &x, float &y, float &z, float mouse_x, float mouse_y);
            ~GetWorldPosition() = default;

            void Execute() override;
        private:
            float &x, &y, &z;
            float mouse_x, mouse_y;
            Action method;
        };

        class GetCameraVectors : public BaseCommand
        {
        using Action = void (*)(float &, float &, float &,
                                float &, float &, float &,
                                float &, float &, float &);
        public:
            GetCameraVectors() = delete;
            GetCameraVectors(float &x1, float &y1, float &z1,
                             float &x2, float &y2, float &z2,
                             float &x3, float &y3, float &z3);
            ~GetCameraVectors() = default;

            void Execute() override;
        private:
            float &x1, &y1, &z1;
            float &x2, &y2, &z2;
            float &x3, &y3, &z3;
            Action method;
        };
    }
}

#include "Interaction.hpp"

#endif
