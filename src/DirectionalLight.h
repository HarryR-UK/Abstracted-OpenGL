#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm/glm.hpp>

namespace ge
{
    struct DirectionalLight
    {
        glm::vec3 direction = glm::vec3(-0.5f, -0.5f, 0.8f);
        glm::vec3 ambient = glm::vec3(0.3f, 0.3f, 0.3f);
        glm::vec3 diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
        glm::vec3 specular = glm::vec3(0.2f, 0.2f, 0.2f);

    };

};


#endif