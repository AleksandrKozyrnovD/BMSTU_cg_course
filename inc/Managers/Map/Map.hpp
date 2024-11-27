#include "Map.h"

Map::Map()
: w(1), h(1)
{
    this->map = std::vector<std::vector<Plot>>(w, std::vector<Plot>(h));
}

Map::Map(size_t w, size_t h)
: w(w), h(h)
{
    this->map = std::vector<std::vector<Plot>>(w, std::vector<Plot>(h));
}

Map::Map(size_t size)
: w(size), h(size)
{
    this->map = std::vector<std::vector<Plot>>(w, std::vector<Plot>(h));
}

void Map::set_building(size_t x, size_t y, std::shared_ptr<AbstractObject>& obj, Facing facing)
{
    //general case. outside of map
    if (!(y > 0 && x > 0 && x < w && y < h))
    {
        return;
    }

    switch (facing)
    {
        case Facing::NORTH:
            // if (y + 1 < h)
            {
                map[x][y].object = obj;
                map[x][y].empty = false;
                // map[x][y + 1].object = obj;
            }
            break;
        case Facing::SOUTH:
            // if (y - 1 >= 0)
            {
                map[x][y].object = obj;
                map[x][y].empty = false;
                // map[x][y - 1].object = obj;
            }
            break;
        case Facing::EAST:
            // if (x + 1 < w)
            {
                map[x][y].object = obj;
                map[x][y].empty = false;
                // map[x + 1][y].object = obj;
            }
            break;
        case Facing::WEST:
            // if (x - 1 >= 0)
            {
                map[x][y].object = obj;
                map[x][y].empty = false;
                // map[x - 1][y].object = obj;
            }
    }
}

void Map::set_floor(size_t x, size_t y, std::shared_ptr<AbstractObject>& floor, Facing facing)
{
    //general case. outside of map
    if (!(y > 0 && x > 0 && x < w && y < h))
    {
        return;
    }

    switch (facing)
    {
        case Facing::NORTH:
            map[x][y].floor = floor;
            break;
        case Facing::SOUTH:
            map[x][y].floor = floor;
            break;
        case Facing::EAST:
            map[x][y].floor = floor;
            break;
        case Facing::WEST:
            map[x][y].floor = floor;
            break;
    }
}