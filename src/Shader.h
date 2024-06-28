#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>
#include<OpenGL/gl.h>

#include<sys/stat.h>
#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<fstream>
#include<unistd.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


class Shader
{
    private:
        unsigned int vertID = -1;
        unsigned int fragID = -1;
        unsigned int geoID = -1;

        std::string m_vertSrcPath;
        std::string m_fragSrcPath;

    private:
        inline static bool fileExists(std::string& path);

        void compileShader(const char* src, GLenum shaderType);
        void printDebugShader(unsigned int& shaderID, GLenum shaderType);
        std::stringstream getSource(std::string& path);

        void printDebugProgram();
        void linkProgram();

    public:
        unsigned int ID;
    public:
        Shader(std::string vertSrcPath, std::string fragSrcPath);
        Shader();
        void setShaderSrc(std::string vertSrcPath, std::string fragSrcPath);
        
        void setShaderCode(const char* vertCode, const char* fragCode);


        void recompile();

        void use();
        // uniform methods
        void setFloat(const std::string& name, float value) const;
        void setInt(const std::string& name, int value) const;

        void setMat4(const std::string& name, glm::mat4 value) const;

        void setVec3(const std::string& name, glm::vec3 value) const;
        void setVec2(const std::string& name, glm::vec2 value) const;

        void setUBOBinding(const std::string& uniformBlockName, const int& bindingPoint);
        
        static void unbind();

};

#endif //!SHADER_H