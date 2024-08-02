#ifndef __FACADE_H__
#define __FACADE_H__

#include "CommandClasses/BaseCommand.h"

class Facade
{
public:
    static void initialize();

    static void execute(BaseCommand* command)
    {
        command->Execute();
    }
};


#endif

