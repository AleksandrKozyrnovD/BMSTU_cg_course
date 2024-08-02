#ifndef __SCENE_TRANSFORM_H__
#define __SCENE_TRANSFORM_H__

#include "AbstractObject.h"
#include "CommandClasses/BaseCommand.h"


namespace Actions
{
    namespace Scene
    {
        class AddObject : public BaseCommand
        {
        using Action = void (*)(std::shared_ptr<AbstractObject>);
        public:
            AddObject() = delete;
            explicit AddObject(std::shared_ptr<AbstractObject>& object);
            ~AddObject() = default;

            void Execute() override;
        private:
            std::shared_ptr<AbstractObject>& obj;
            Action method;
        };

        class RemoveObject : public BaseCommand
        {
        using Action = void (*)(size_t);
        public:
            RemoveObject() = delete;
            RemoveObject(std::shared_ptr<AbstractObject>& object, size_t id);
            ~RemoveObject() = default;

            void Execute() override;
        private:
            std::shared_ptr<AbstractObject>& obj;
            size_t id;
            Action method;
        };

        class GetObject : public BaseCommand
        {
        using Action = std::shared_ptr<AbstractObject> (*)(size_t);
        public:
            GetObject() = delete;
            GetObject(std::shared_ptr<AbstractObject>& object, size_t id);
            ~GetObject() = default;

            void Execute() override;
        private:
            std::shared_ptr<AbstractObject>& obj;
            size_t id;
            Action method;
        };

        class GetObjects : public BaseCommand
        {
        using Action = std::vector<std::shared_ptr<AbstractObject>> (*)();
        public:
            GetObjects() = delete;
            GetObjects(std::shared_ptr<AbstractObject>& object);
            ~GetObjects() = default;

            void Execute() override;
        private:
            std::shared_ptr<AbstractObject>& obj;
            Action method;
        };

        class ClearScene : public BaseCommand
        {
        using Action = void (*)();
        public:
            ClearScene() = default;
            ~ClearScene() = default;

            void Execute() override;
        };

        class AddCamera : public BaseCommand
        {
        using Action = void (*)(std::shared_ptr<AbstractObject>);
        public:
            AddCamera() = delete;
            explicit AddCamera(std::shared_ptr<AbstractObject>& object);
            ~AddCamera() = default;

            void Execute() override;
        private:
            std::shared_ptr<AbstractObject>& obj;
            Action method;
        };

        class RemoveCamera : public BaseCommand
        {
        using Action = void (*)(size_t);
        public:
            RemoveCamera() = delete;
            explicit RemoveCamera(size_t id);
            ~RemoveCamera() = default;

            void Execute() override;
        private:
            size_t id;
            Action method;
        };
        
        class SetCamera : public BaseCommand
        {
        using Action = void (*)(size_t);
        public:
            SetCamera() = delete;
            explicit SetCamera(size_t id);
            ~SetCamera() = default;

            void Execute() override;
        private:
            size_t id;
            Action method;
        };

        class GetMainCamera : public BaseCommand
        {
        using Action = std::shared_ptr<Camera> (*)();
        public:
            GetMainCamera() = delete;
            explicit GetMainCamera(size_t id);
            ~GetMainCamera() = default;

            void Execute() override;
        private:
            Action method;
            size_t id;
        };
    }
}

#include "Transform.hpp"

#endif
