#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <iostream>

#include "Shader.h"
#include "Global.h"


namespace ge
{
    class Framebuffer
    {
        private:
            Shader m_shader;
        private:
            void setupMesh();

        public:
            GLuint ID;
            GLuint textureID;
            GLuint renderBufferID;

            GLuint VAO, VBO, EBO;
            


        public:
            Framebuffer();
            ~Framebuffer();

            void setup(const char* vertSrc, const char* fragSrc);
            void listenToRenderCalls();

            void renderFramebufferToScreen();

        public:
            static void useDefault();

    };
};


#endif //!FRAMEBUFFER_H