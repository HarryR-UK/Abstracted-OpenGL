#ifndef SKYBOX_H
#define SKYBOX_H

#define LOG(x) std::cout << x << '\n'

#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "stb_image.h"
#include "Shader.h"


#define DEBUG

namespace ge
{
    class Skybox
    {
        private:
            const char* m_vertSrc = 

                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "\n"
                "out vec3 TexCoords;\n"
                "\n"
                "layout (std140) uniform Camera\n"
                "{\n"
                "   mat4 projection;\n"
                "   mat4 view;\n"
                "}cam;\n"
                
                "void main()\n"
                "{\n"
                "   TexCoords = aPos;\n"
                "   mat4 newView = mat4(mat3(cam.view));\n"
                "   vec4 pos = cam.projection * newView * vec4(aPos, 1.0);\n"
                "   gl_Position = pos.xyww;\n"
                "}\n\0";


            const char* m_fragSrc =  
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "\n"
                "in vec3 TexCoords;\n"
                "\n"
                "uniform samplerCube skybox;\n"
                "\n"
                "void main()\n"
                "{\n"
                "   FragColor = texture(skybox, TexCoords);\n"
                "}\n\0";

            std::vector<std::string> m_faces;
            Shader m_shader;

            
            GLuint VAO, VBO;



        private:
            void loadCubemap()
            {
                glGenTextures(1, &this->textureID);
                glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

                int width, height, nrChannels;
                for (GLuint i = 0; i < m_faces.size(); ++i)
                {
                    unsigned char* data = stbi_load(m_faces[i].c_str(), &width, &height, &nrChannels, 0);
                    if(data)
                    {
                        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                        );

                        stbi_image_free(data);
                    }
                    else
                    {
                        std::cout << "Cubemap texture failed to load at path: " << m_faces[i] << '\n';
                        stbi_image_free(data);
                    }

                }

                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            }

            void setUpMesh()
            {
                    float skyboxVertices[] = {
                    // positions          
                    -1.0f,  1.0f, -1.0f,
                    -1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f,  1.0f, -1.0f,
                    -1.0f,  1.0f, -1.0f,

                    -1.0f, -1.0f,  1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f,  1.0f, -1.0f,
                    -1.0f,  1.0f, -1.0f,
                    -1.0f,  1.0f,  1.0f,
                    -1.0f, -1.0f,  1.0f,

                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,

                    -1.0f, -1.0f,  1.0f,
                    -1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f, -1.0f,  1.0f,
                    -1.0f, -1.0f,  1.0f,

                    -1.0f,  1.0f, -1.0f,
                    1.0f,  1.0f, -1.0f,
                    1.0f,  1.0f,  1.0f,
                    1.0f,  1.0f,  1.0f,
                    -1.0f,  1.0f,  1.0f,
                    -1.0f,  1.0f, -1.0f,

                    -1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f,  1.0f
                };
                glGenVertexArrays(1, &VAO);
                glBindVertexArray(VAO);

                glGenBuffers(1, &VBO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*) 0);
                glEnableVertexAttribArray(0);

                glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);


            }

            void setupShader()
            {
            }

        public:
            GLuint textureID;
        public:
            Skybox(std::vector<std::string> faces)
            {
                setup(faces);
            }

            Skybox()
            {

            }

            void setup(std::vector<std::string> faces)
            {
                this->m_shader.setShaderCode(this->m_vertSrc, this->m_fragSrc);
                this->m_faces = faces;

                this->setUpMesh();
                this->loadCubemap();
            }

            void Draw()
            {
                glDepthFunc(GL_LEQUAL);
                m_shader.use();

                glBindVertexArray(VAO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                glDepthFunc(GL_LESS);
            }

            void updateProjections(glm::mat4 view, glm::mat4 projection)
            {
                glm::mat4 updateView = glm::mat4(glm::mat3(view));
                m_shader.use();
                m_shader.setMat4("u_view", updateView);
                m_shader.setMat4("u_projection", projection);
            }

            void setUBOBinding(const std::string& name, const int& bindPoint)
            {
                m_shader.setUBOBinding(name, bindPoint);
            }

            void use()
            {
                glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
            }

            Shader& getShader() {return this->m_shader;}

    };
} // namespace ge

#endif