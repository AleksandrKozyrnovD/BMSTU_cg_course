#ifndef __FACET_H__
#define __FACET_H__

#include "Plane.h"

#include "glm/mat4x4.hpp"
#include <cstdint>


class DrawVisitor;

class Facet : public Surface
{
friend class DrawVisitor;
friend class ZMapper;
friend class LightCaster;
friend class NewDrawVisitor;

public:
    Facet() = default;
    Facet(const Facet& other) = default;
    Facet(Facet&& other) noexcept = default;
    
    Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, uint32_t color = 0xff0000ff) noexcept;
    Facet(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, bool direction, uint32_t color = 0xff0000ff) noexcept;

    ~Facet() = default;

    Facet& operator=(const Facet& other);
    Facet& operator=(Facet&& other) noexcept;

    void move(const glm::vec3& delta);
    void rotate(const glm::vec3 angles);
    void scale(const glm::vec3& scale);
    void scale(float scalar);

    void transform(const glm::mat4x4& transformation);

    glm::vec3 get_center() const;

    void fix_direction(const glm::vec3& center);

public:
    uint32_t color;
};

#include "Facet.hpp"

#endif