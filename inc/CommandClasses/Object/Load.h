#ifndef __OBJECT_LOAD_H__
#define __OBJECT_LOAD_H__

#include "CommandClasses/BaseCommand.h"

#include "LoadManager.h"

namespace Actions
{
    namespace Object
    {
        class LoadTXTUncolored : public BaseCommand
        {
        using Action = std::shared_ptr<AbstractObject> (*)(const std::string&);
        public:
            LoadTXTUncolored() = delete;
            explicit LoadTXTUncolored(std::shared_ptr<AbstractObject>& obj, const std::string& filename);
            ~LoadTXTUncolored() = default;

            void Execute() override;
        
        private:
            std::shared_ptr<AbstractObject>& obj;
            std::string filename;
            Action method;
        };
    }
}

#include "Load.hpp"

#endif
