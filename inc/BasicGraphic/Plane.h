#ifndef __PLANE_H__
#define __PLANE_H__

#include <glm/vec3.hpp>

class Surface
{
public:
    Surface() = default;
    explicit Surface(const Surface& other);
    Surface(Surface&& other) noexcept;
    
    Surface(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) noexcept;
    Surface(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, bool direction) noexcept;

    ~Surface() = default;

    Surface& operator=(const Surface& other);

    const glm::vec3& get_normal() const;
    const glm::vec3& operator*() const;

    void change_direction();
    glm::vec3 A, B, C;

protected:
    glm::vec3 normal;
};

#include "Plane.hpp"

#endif