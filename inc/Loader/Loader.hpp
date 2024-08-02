#include "Loader.h"

std::shared_ptr<AbstractObject> Loader::load(std::shared_ptr<BaseDirector> director)
{
    return director->create();
}

