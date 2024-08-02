#ifndef BASEDIRECTOR_H
#define BASEDIRECTOR_H

#include "../../Objects/AbstractObject.h"

class BaseDirector
{
public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    
    virtual std::shared_ptr<AbstractObject> create() = 0;
};

#endif // BASEDIRECTOR_H