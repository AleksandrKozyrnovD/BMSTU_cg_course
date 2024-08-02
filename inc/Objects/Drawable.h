#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "AbstractObject.h"

class Drawable : public AbstractObject
{
public:
    Drawable() = default;
    ~Drawable() override = default;

    bool IsDrawable() override { return true; }
};

class Undrawable : public AbstractObject
{
public:
    Undrawable() = default;
    ~Undrawable() override = default;

    bool IsDrawable() override { return false; }
};



#endif