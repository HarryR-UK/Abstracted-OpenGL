#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "../Shader.h"
#include "VerletObject.h"
#include "StaticObject.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Global.h"

typedef glm::vec3 vec3;

namespace ge
{
    class Simulator
    {
        private:
            ge::Window* m_window;
            Shader m_constraintShader;
            ge::StaticObject m_constraintObject;

            float m_deltaTime;
            float m_time;
            int m_subStepNumber;

            vec3 m_gravity = vec3(0.0f, 10.f,0.0f);
            
            std::vector<VerletObject> m_objects = {};

            vec3 m_constraintPosition = vec3(0.2f, -0.5f, 0.0f);
            float m_constraintRadius = 20.0f;

        private:
            void updateObjects(float subDeltaTime);
            void updateGravity();
            void checkCollisions();
            void checkConstraints();
            void setupConstraint();

        public:

        public:
            Simulator();
            void initialise();
            void render(Shader& shader);
            void renderConstraint();
            void update( float deltaTime );
            float getSubDeltaTime();
            void setWindow(ge::Window* window);
    };
} // namespace ge


#endif // !SIMULATOR_H