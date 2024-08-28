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

        class GetCameraPos : public BaseCommand
        {
        using Action = void (*)(float &, float &, float &);
        public:
            GetCameraPos() = delete;
            explicit GetCameraPos(float &x, float &y, float &z);
            ~GetCameraPos() = default;

            void Execute() override;
        private:
            float &x, &y, &z;
            Action method;
        };

        class GetObjectTranslation : public BaseCommand
        {
        using Action = void (*)(size_t, float &, float &, float &);
        public:
            GetObjectTranslation() = delete;
            explicit GetObjectTranslation(size_t id, float &x, float &y, float &z);
            ~GetObjectTranslation() = default;

            void Execute() override;
        private:
            size_t id;
            float &x, &y, &z;
            Action method;
        };

        class GetObjectRotation : public BaseCommand
        {
        using Action = void (*)(size_t, float &, float &, float &);
        public:
            GetObjectRotation() = delete;
            explicit GetObjectRotation(size_t id, float &x, float &y, float &z);
            ~GetObjectRotation() = default;

            void Execute() override;
        private:
            size_t id;
            float &x, &y, &z;
            Action method;
        };

        class GetObjectScale : public BaseCommand
        {
        using Action = void (*)(size_t, float &, float &, float &);
        public:
            GetObjectScale() = delete;
            explicit GetObjectScale(size_t id, float &x, float &y, float &z);
            ~GetObjectScale() = default;

            void Execute() override;
        private:
            size_t id;
            float &x, &y, &z;
            Action method;
        };

        class MoveObjectScene : public BaseCommand
        {
        using Action = void (*)(size_t, float, float, float);
        public:
            MoveObjectScene() = delete;
            explicit MoveObjectScene(size_t id, float x, float y, float z);
            ~MoveObjectScene() = default;

            void Execute() override;
        private:
            size_t id;
            float x, y, z;
            Action method;
        };

        class RotateObjectScene : public BaseCommand
        {
        using Action = void (*)(size_t, float, float, float);
        public:
            RotateObjectScene() = delete;
            explicit RotateObjectScene(size_t id, float x, float y, float z);
            ~RotateObjectScene() = default;

            void Execute() override;
        private:
            size_t id;
            float x, y, z;
            Action method;
        };

        class ScaleObjectScene : public BaseCommand
        {
        using Action = void (*)(size_t, float, float, float);
        public:
            ScaleObjectScene() = delete;
            explicit ScaleObjectScene(size_t id, float x, float y, float z);
            ~ScaleObjectScene() = default;

            void Execute() override;
        private:
            size_t id;
            float x, y, z;
            Action method;
        };
    }
}

#include "Interaction.hpp"

#endif
