#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "Camera.h"
#include "Time.h"

namespace ge{
    class Window
    {
        private:
            GLFWwindow* m_window;
            bool m_keyIsHeld = false;

        private:
            static inline bool s_isCursorVisible = false;
        private:
            void clearBuffers()
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            }

        private:
            static inline void mouseCallBack(GLFWwindow* window, double xPos, double yPos)
            {
                float xOffset = xPos - s_mouseLastXPosition;
                float yOffset = s_mouseLastYPosition - yPos;

                s_mouseLastXPosition = xPos;
                s_mouseLastYPosition = yPos;

                if(!s_isCursorVisible)
                    ge::Camera::processMouseMovement(xOffset, yOffset);
            }


        public:

        public:
            static inline float s_mouseLastXPosition = 0.0f;
            static inline float s_mouseLastYPosition = 0.0f;


        public:

            GLFWwindow* getWindow() {return this->m_window;}

            void setupWindow(int w, int h, std::string title, int max, int min, bool fullscreen=false)
            {
                if(!glfwInit())
                {
                    std::cout << "ERROR INIT GLFW" << '\n';
                    std::exit(1);
                }
                
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, false);
                glfwWindowHint(GLFW_RESIZABLE, false);
                glfwWindowHint(GLFW_SAMPLES, 4);
                #if __APPLE__
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
                #endif //!__APPLE__


                m_window = (!fullscreen) ? glfwCreateWindow(w, h, title.c_str(), NULL, NULL) 
                : glfwCreateWindow(w, h, title.c_str(), glfwGetPrimaryMonitor(), NULL);

                glfwMakeContextCurrent(m_window);


                glewExperimental = GL_TRUE;

                if(glewInit() != GLEW_OK)
                {
                    std::cout << "ERROR INIT GLEW" << '\n';
                    std::exit(1);
                }

                glEnable(GL_DEPTH_TEST);
                glEnable(GL_STENCIL_TEST);
                glEnable(GL_CULL_FACE);
                glEnable(GL_BLEND);

                glCullFace(GL_FRONT);
                glFrontFace(GL_CW);
                
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                //glEnable(GL_MULTISAMPLE);
                glEnable(GL_PROGRAM_POINT_SIZE);   

                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(m_window, mouseCallBack);
                
            }

            bool isOpen() {return !glfwWindowShouldClose(m_window);}

            void display() {glfwSwapBuffers(m_window);}
            
            void pollEvents(){glfwPollEvents();}

            void clear()
            {
                glClearColor(0.0f,0.0f,0.0f,1.0f);
                clearBuffers();
            }

            void clear(float r, float g, float b, float a)
            {
                glClearColor(r,g,b,a);
                clearBuffers();
            }

            void processInput()
            {
                if(!s_isCursorVisible)
                {
                    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::FORWARD, ge::Time::deltaTime);
                    }
                    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
                    {

                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::BACKWARD, ge::Time::deltaTime);
                    }
                    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
                    {

                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::LEFT, ge::Time::deltaTime);
                    }
                    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
                    {

                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::RIGHT, ge::Time::deltaTime);
                    }
                    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::UP, ge::Time::deltaTime);
                    }
                    if(glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::CameraMovementType::DOWN, ge::Time::deltaTime);
                    }

                }

                if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                {
                    if(!m_keyIsHeld)
                    {
                        m_keyIsHeld = true;

                        if(Window::s_isCursorVisible)
                        {
                            s_isCursorVisible = false;
                            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        }
                        else
                        {
                            s_isCursorVisible = true;
                            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        }
                    }
                }
                else{
                    m_keyIsHeld = false;
                }


                
                
            }



            void setWindowTitle(std::string title)
            {
                glfwSetWindowTitle(m_window, title.c_str());
            }



        
    };
};

#endif