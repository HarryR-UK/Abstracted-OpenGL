#ifndef VERLET_OBJECT_H
#define VERLET_OBJECT_H

#include "../Model.h"
#include "../Transform.h"
#include "../Material.h"
#include <glm/glm.hpp>

typedef glm::vec3 vec3;

namespace ge
{
    struct VerletObject
    {
        Model model;
        ge::Transform transform;
        ge::Material material;
        float radius = 1.0f;
        float mass;
        float friction = 0.1f;
        glm::vec3 oldPosition;
        glm::vec3 acceleration;
        glm::vec3 color = glm::vec3(1.0f);



        VerletObject(const char* modelPath, float radius, vec3 startPos);
        VerletObject();
        void setup(const char* modelPath, float radius, vec3 startPos);
        void update( float deltaTime );
        void accelerate( glm::vec3 acc );
        void setVelocity( glm::vec3 vel, float deltaTime );
        void addVelocity( glm::vec3 vel, float deltaTime );
        void Draw(Shader& shader);

    };
} // namespace ge



#endif // !VERLET_OBJECT_H