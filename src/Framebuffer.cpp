#include "Framebuffer.h"


namespace ge
{
    Framebuffer::Framebuffer()
    {

    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &ID);
    }

    void Framebuffer::setup(const char* vertSrc, const char* fragSrc)
    {
        m_shader.setShaderSrc(vertSrc, fragSrc); 
        setupMesh();


        glGenFramebuffers(1, &ID);
        glBindFramebuffer(GL_FRAMEBUFFER, ID); 

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ge::WINDOW_WIDTH, ge::WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);


        glGenRenderbuffers(1, &renderBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ge::WINDOW_WIDTH, ge::WINDOW_HEIGHT);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);


        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR FRAMEBUFFER IS NOT COMPLETE" << '\n';
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void Framebuffer::setupMesh()
    {
            float quadVertices[] = {  
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
            };	



            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);



            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);


            // positions
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*) 0);
            glEnableVertexAttribArray(0);

            // Tex coords
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*) (2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindVertexArray(0);

    }


    void Framebuffer::listenToRenderCalls()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, ID); 
    }

    void Framebuffer::renderFramebufferToScreen()
    {
        Framebuffer::useDefault();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glDisable(GL_DEPTH_TEST);

        glBindTexture(GL_TEXTURE_2D, textureID);
        //m_shader.setInt("screenTexture", 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Framebuffer::useDefault()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

};