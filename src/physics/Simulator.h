#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <thread>

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

            int m_timeSpawner = 0;
            int m_timeBetween = 0;
            int m_spawnerDelay = 100;
            int m_maxBalls = 300;
            int m_currentBalls = 0;

            vec3 m_gravity = vec3(0.0f, 20.f,0.0f);
            
            std::vector<VerletObject> m_objects = {};

            float m_constraintRadius = 30.0f;



        private:
            void updateObjects(float subDeltaTime);
            void updateGravity();
            void updateConstraintMatrix();
            void checkCollisions();
            void checkConstraints(float subDT);
            void setupConstraint();
            float calculateDistance(vec3 axis);
            void spawnObjects();


        public:

        public:
            Simulator();
            void initialise();
            void render(Shader& shader);
            void renderConstraint();
            void update( float deltaTime );
            float getSubDeltaTime();
            void setWindow(ge::Window* window);
            void startThreads();
    };
} // namespace ge


#endif // !SIMULATOR_H