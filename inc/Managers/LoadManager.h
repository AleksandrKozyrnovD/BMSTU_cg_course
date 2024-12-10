#ifndef __LOAD_MANAGER_H__
#define __LOAD_MANAGER_H__

#include "BaseManager.h"

#include "Builders/AbstractSurfaceBuilder.h"
#include "Builders/BaseDirector.h"
#include "Builders/SurfaceDirector.h"
#include "Builders/DirectorCreator.h"
#include "Light.h"
#include "Readers/TXTFacetReader.h"
#include "Readers/AbstractFacetReader.h"

#include <memory>


namespace ControlSystem
{
    class LoadManager : public BaseManager
    {
    public:


        template<typename builder>
            requires std::derived_from<builder, AbstractSurfaceBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractFacetReader>>
        static std::shared_ptr<AbstractObject> load_from_file(const std::string& filename)
        {
            std::shared_ptr<AbstractFacetReader> reader = std::make_shared<TXTFacetReader>(filename);
            std::shared_ptr<AbstractSurfaceBuilder> _builder = std::make_shared<builder>(reader);
            std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<SurfaceDirector>(_builder);

            return myDirector->create();
        }
        template<typename builder>
            requires std::derived_from<builder, AbstractSurfaceBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractFacetReader>>
        static std::shared_ptr<AbstractObject> load_from_binary(const std::string& filename)
        {
            std::shared_ptr<AbstractFacetReader> reader = std::make_shared<TXTFacetReader>(filename);
            std::shared_ptr<AbstractSurfaceBuilder> _builder = std::make_shared<builder>(reader);
            std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<SurfaceDirector>(_builder);

            return myDirector->create();
        }

        static std::shared_ptr<AbstractObject> load_composite_object(const std::string& filename);

        static std::shared_ptr<Camera> load_camera(const std::string& filename);

        static std::shared_ptr<Light> load_light(const std::string& filename);

        static void load_scene(const std::string& filename);
    };
}

#include "LoadManager.hpp"

#endif
