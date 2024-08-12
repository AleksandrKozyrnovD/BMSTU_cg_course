#include "Slope.h"

Slope::Slope()
    : cur(0), step()
{}

Slope::Slope(float begin, float end, float num_steps, float advance)
{
    float inv_step = 1.0f / num_steps;
    step = (end - begin) * inv_step;  // Stepsize = (end-begin) / num_steps
    cur  = begin + step * advance;    // Begin here
}

float Slope::get() const
{
    return this->cur;
}

void Slope::advance()
{
    this->cur += step;
}

void Slope::advance(float n)
{
    this->cur += n * step;
}


GLMSlope::GLMSlope()
    : cur(), step()
{}

GLMSlope::GLMSlope(const glm::vec3& begin, const glm::vec3& end, float num_steps, float advance)
{
    float inv_step = 1.0f / num_steps;
    step = (end - begin) * inv_step;  // Stepsize = (end-begin) / num_steps
    cur  = begin + step * advance;    // Begin here
}

glm::vec3 GLMSlope::get() const
{
    return this->cur;
}

void GLMSlope::advance()
{
    this->cur += step;
}

void GLMSlope::advance(float n)
{
    this->cur += n * step;
}