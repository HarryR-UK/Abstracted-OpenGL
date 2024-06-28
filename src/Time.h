#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

namespace ge
{
    class Time
    {
        private:
            static inline float currentFrameTime = 0.0f;
            static inline float lastFrameTime = 0.0f;
        private:

        public:
            static inline float deltaTime = 0.0f;
            static inline float time = 0.0f;

            static inline int fps = 0;

        public:
            static void update()
            {
                time = glfwGetTime();

                currentFrameTime = glfwGetTime();
                deltaTime = currentFrameTime - lastFrameTime;

                fps = (int) 1/deltaTime;

                lastFrameTime = currentFrameTime;


            }

    };
};

#endif