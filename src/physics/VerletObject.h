#ifndef VERLET_OBJECT_H
#define VERLET_OBJECT_H

#include "../Model.h"
#include "../Transform.h"
#include <glm/glm.hpp>

typedef glm::vec3 vec3;

namespace ge
{
    class VerletObject
    {
        private:




        private:

        public:
            Model model;
            ge::Transform transform;
            float radius = 1.0f;
            float mass;
            glm::vec3 oldPosition;
            glm::vec3 acceleration;
        public:
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