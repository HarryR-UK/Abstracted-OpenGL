#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>



namespace ge
{
    class Time
    {
        private:
        private:

        public:
            static inline float deltaTime = 0.0f;
            static inline float time = 0.0f;
            static inline float currentFrameTime = 0.0f;
            static inline float lastFrameTime = 0.0f;

            static inline int fps = 0;

        public:


    };
};

#endif