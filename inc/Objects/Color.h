#ifndef __COLOR_H__
#define __COLOR_H__

#include <glm/vec4.hpp>

enum Color
{
    WHITE = 0,
    BLACK,
    GRAY,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    ORANGE
};

glm::vec4 getColor(Color color)
{
    switch (color)
    {
        case WHITE:
            return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        case BLACK:
            return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        case GRAY:
            return glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        case RED:
            return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        case GREEN:
            return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        case BLUE:
            return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        case YELLOW:
            return glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        case CYAN:
            return glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        case MAGENTA:
            return glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
        case ORANGE:
            return glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
        default:
            return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}

#endif
