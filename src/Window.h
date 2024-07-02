#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/OpenGL.h>
#include <string>
#include <iostream>

#include "Camera.h"
#include "Time.h"

namespace ge{
    class Window
    {
        private:
            SDL_Window* m_window;
            SDL_GLContext m_context;
            bool m_keyIsHeld = false;
            SDL_Scancode m_keyPressed;

        private:
            static inline bool s_isCursorVisible = false;

            bool KEYS[322];

        private:
            void clearBuffers()
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            }

        private:
        /*
            static inline void mouseCallBack(GLFWwindow* window, double xPos, double yPos)
            {
                float xOffset = xPos - s_mouseLastXPosition;
                float yOffset = s_mouseLastYPosition - yPos;

                s_mouseLastXPosition = xPos;
                s_mouseLastYPosition = yPos;

                if(!s_isCursorVisible)
                    ge::Camera::processMouseMovement(xOffset, yOffset);
            }

            */



        public:
            bool windowOpen = true;
        public:
            static inline float s_mouseLastXPosition = 0.0f;
            static inline float s_mouseLastYPosition = 0.0f;



        public:

            SDL_Window* getWindow() {return this->m_window;}

            void setupWindow(int w, int h, std::string title, int max, int min, bool fullscreen=false)
            {
                SDL_Init(SDL_INIT_VIDEO);

                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, max);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, min);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

                m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ge::WINDOW_WIDTH, ge::WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

                m_context = SDL_GL_CreateContext(m_window);

                glewExperimental = true;

                if(glewInit() != GLEW_OK)
                {
                    std::cout << "ERROR: WITH GLEW" << '\n';
                    exit(1);
                }


                SDL_SetRelativeMouseMode(SDL_TRUE);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_STENCIL_TEST);
                glEnable(GL_CULL_FACE);
                glEnable(GL_BLEND);

                glCullFace(GL_FRONT);
                glFrontFace(GL_CW);
                
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                //glEnable(GL_MULTISAMPLE);
                glEnable(GL_PROGRAM_POINT_SIZE);   

                SDL_ShowCursor(false);

                for(int i = 0; i < 322; ++i)
                {
                    KEYS[i] = false;
                }

                //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                //glfwSetCursorPosCallback(m_window, mouseCallBack);
                
            }

            bool isOpen() {return windowOpen;}

            void display() {SDL_GL_SwapWindow(m_window);}
            
            void pollEvents()
            {
                SDL_Event event;
                while(SDL_PollEvent(&event))
                {
                    if(event.type == SDL_QUIT)
                        windowOpen = false;

                    if(event.type == SDL_MOUSEMOTION && !s_isCursorVisible)
                    {
                        ge::Camera::processMouseMovement(event.motion.xrel, -event.motion.yrel);
                    }

                    if(event.type == SDL_KEYDOWN)
                    {

                    }
                    if(event.type = SDL_KEYUP)
                    {

                    }


                }
            }

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
                    SDL_PumpEvents();
                    const Uint8* state = SDL_GetKeyboardState(NULL);
                    if(state[SDL_SCANCODE_W])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::FORWARD, ge::Time::deltaTime);
                    }
                    if(state[SDL_SCANCODE_S])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::BACKWARD, ge::Time::deltaTime);
                    }
                    if(state[SDL_SCANCODE_A])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::LEFT, ge::Time::deltaTime);
                    }
                    if(state[SDL_SCANCODE_D])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::RIGHT, ge::Time::deltaTime);
                    }
                    if(state[SDL_SCANCODE_SPACE])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::UP, ge::Time::deltaTime);
                    }
                    if(state[SDL_SCANCODE_LCTRL])
                    {
                        ge::Camera::processKeyboardInput(ge::Camera::DOWN, ge::Time::deltaTime);
                    }

                }

                if(m_keyPressed == SDL_SCANCODE_ESCAPE)
                {
                    if(!m_keyIsHeld)
                    {
                        m_keyIsHeld = true;

                        if(Window::s_isCursorVisible)
                        {
                            s_isCursorVisible = false;
                            //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                            SDL_SetRelativeMouseMode(SDL_TRUE);
                            SDL_ShowCursor(SDL_FALSE);
                        }
                        else
                        {
                            s_isCursorVisible = true;
                            //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                            SDL_SetRelativeMouseMode(SDL_FALSE);
                            SDL_ShowCursor(SDL_TRUE);
                        }
                    }
                }
                else{
                    m_keyIsHeld = false;
                }


                
                
            }



            void setWindowTitle(std::string title)
            {
                //glfwSetWindowTitle(m_window, title.c_str());
                SDL_SetWindowTitle(m_window, title.c_str());
            }



        
    };
};

#endif