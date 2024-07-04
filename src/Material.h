#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

typedef glm::vec3 vec3;

namespace ge
{

    struct Material
    {
        vec3 diffuse = vec3(1.0);
        float shininess = 1.f;
    };
} // namespace ge


#endif // !MATERIAL_H