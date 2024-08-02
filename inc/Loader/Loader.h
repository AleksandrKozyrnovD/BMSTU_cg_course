#ifndef __LOADER_H__
#define __LOADER_H__

#include "AbstractObject.h"
#include "Builders/BaseDirector.h"
#include <memory>


class Loader
{
public:
    Loader();
    ~Loader() = default;

    static std::shared_ptr<AbstractObject> load(std::shared_ptr<BaseDirector> director);
};

#include "Loader.hpp"



#endif

