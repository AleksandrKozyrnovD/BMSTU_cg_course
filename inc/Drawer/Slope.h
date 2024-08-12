#ifndef __SLOPE_H__
#define __SLOPE_H__

#include <glm/vec3.hpp>

class Slope
{
public:
    Slope();
    Slope(float begin, float end, float num_steps, float advance=0);


    float get() const;
    void advance();
    void advance(float n);

private:
    float cur, step;
};

class GLMSlope
{
public:
    GLMSlope();
    GLMSlope(const glm::vec3& begin, const glm::vec3& end, float num_steps, float advance=0);

    glm::vec3 get() const;
    void advance();
    void advance(float n);

private:
    glm::vec3 cur, step;
};

#include "Slope.hpp"

#endif
