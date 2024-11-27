#ifndef __MAP_H__
#define __MAP_H__

#include "AbstractObject.h"
#include <memory>
#include <vector>


enum Facing
{
    NORTH = 0,
    EAST,
    WEST,
    SOUTH,
    DEFAULT = NORTH
};

struct Plot
{
public:
    Plot()
    : floor(nullptr), object(nullptr), empty(true)
    {}


    Plot(std::shared_ptr<AbstractObject>& floor, std::shared_ptr<AbstractObject>& object)
    : floor(floor), object(object), empty(false)
    {}

    operator bool() const
    {
        return !empty; 
    }
public:
    std::shared_ptr<AbstractObject> floor;
    std::shared_ptr<AbstractObject> object;
    bool empty;
};


struct Map
{
    Map();
    Map(size_t w, size_t h);
    explicit Map(size_t size);
    ~Map() = default;

    void set_building(size_t x, size_t y, std::shared_ptr<AbstractObject>& obj, Facing facing = Facing::NORTH);
    void set_floor(size_t x, size_t y, std::shared_ptr<AbstractObject>& floor, Facing facing = Facing::NORTH);

public:
    std::vector<std::vector<Plot>> map;
    size_t w, h;
};

#include "Map.hpp"


#endif
