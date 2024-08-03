#ifndef __FACADE_H__
#define __FACADE_H__

#include "CommandClasses/BaseCommand.h"

namespace ControlSystem
{
    class Facade
    {
    public:
        static void initialize();

        static inline void execute(Actions::BaseCommand* command) { command->Execute(); }
    };
}

#include "Facade.hpp"

#endif

