#ifndef __LOAD_MANAGER_H__
#define __LOAD_MANAGER_H__

#include "BaseManager.h"

#include "Builders/AbstractSurfaceBuilder.h"
#include "Builders/BaseDirector.h"
#include "Builders/SurfaceDirector.h"
#include "Builders/DirectorCreator.h"
#include "Readers/UncoloredTXTFacetReader.h"
#include "Readers/AbstractFacetReader.h"


namespace ControlSystem
{
    class LoadManager : public BaseManager
    {
    public:


        template<typename builder>
            requires std::derived_from<builder, AbstractSurfaceBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractFacetReader>>
        static std::shared_ptr<AbstractObject> load_from_file(const std::string& filename)
        {
            std::shared_ptr<AbstractFacetReader> reader = std::make_shared<UncoloredTXTFacetReader>(filename);
            std::shared_ptr<AbstractSurfaceBuilder> _builder = std::make_shared<builder>(reader);
            std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<SurfaceDirector>(_builder);

            return myDirector->create();
        }
        template<typename builder>
            requires std::derived_from<builder, AbstractSurfaceBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractFacetReader>>
        static std::shared_ptr<AbstractObject> load_from_binary(const std::string& filename)
        {
            std::shared_ptr<AbstractFacetReader> reader = std::make_shared<UncoloredTXTFacetReader>(filename);
            std::shared_ptr<AbstractSurfaceBuilder> _builder = std::make_shared<builder>(reader);
            std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<SurfaceDirector>(_builder);

            return myDirector->create();
        }
    };
}

#endif
