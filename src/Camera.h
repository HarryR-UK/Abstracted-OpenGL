#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Global.h"
#include "Time.h"

namespace ge
{
    typedef glm::vec3 vec3;
    typedef glm::mat4 mat4;

    class Camera
    {
        private:

        private:
            static void setUpUBO()
            {
                glGenBuffers(1, &UBO);
                glBindBuffer(GL_UNIFORM_BUFFER, UBO);
                glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_UNIFORM_BUFFER, 0);

                glBindBufferRange(GL_UNIFORM_BUFFER, ge::CAMERA_UBO_INDEX, UBO, 0, 2*sizeof(glm::mat4));

            }

        public:
            static inline glm::vec3 position = vec3(0.0f, 0.0f, -3.0f);
            static inline glm::vec3 up = vec3(0.0f, 1.0f, 0.0f);
            static inline glm::vec3 forwards; //= vec3(0.0f, 0.0f, -1.0f);
            static inline glm::vec3 right;// = vec3(1.0f, 0.0f, 0.0f);
            
            static inline float yaw = 90.0f;
            static inline float pitch = 0.0f;

            static inline float moveSpeed = 7.0f;
            static inline float sprintSpeed = 5.0f;
            static inline float mouseSens = 0.05f;
            static inline float fov = 65.0f;
            

            static inline GLuint UBO;



        public:
            enum CameraMovementType{
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT,
                UP,
                DOWN,
                SPRINT
            };

            
        public:
            static glm::mat4 getViewMatrix(){ return glm::lookAt(position, position + forwards, up); }
            static glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(fov), (float) ge::WINDOW_WIDTH/ (float) ge::WINDOW_HEIGHT, 0.001f, 100.0f);}

            static void setup()
            {
                setUpUBO();
            }

            static void updateCameraUBO()
            {
                glBindBuffer(GL_UNIFORM_BUFFER, UBO);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(getProjectionMatrix()));
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(getViewMatrix()));
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }

            static void updateCameraVectors()
            {
                forwards = glm::normalize(
                    vec3(
                        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                        sin(glm::radians(pitch)),
                        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
                    )
                );

                right = glm::normalize(glm::cross(forwards, vec3(0.0f, 1.0f, 0.0f)));
                up = glm::normalize(glm::cross(right, forwards));
            }
            static void processMouseMovement(float xOff, float yOff)
            {
                xOff *= mouseSens;
                yOff *= mouseSens;

                yaw += xOff;
                pitch += yOff;

                if(pitch > 89.9f)
                    pitch = 89.9f;
                if(pitch < -89.9f)
                    pitch = -89.9f;

                updateCameraVectors();
            }

            static void processKeyboardInput(CameraMovementType direction, float deltaTime)
            {
                glm::vec3 moveDir = glm::vec3(0.0f);
                float speed = moveSpeed * deltaTime;

                switch (direction)
                {
                case FORWARD:
                    moveDir.x += forwards.x;
                    moveDir.z += forwards.z;
                    break;
                case BACKWARD:
                    moveDir.x -= forwards.x;
                    moveDir.z -= forwards.z;
                    break;
                case LEFT:
                    moveDir -= right;
                    break;
                case RIGHT:
                    moveDir += right;
                    break;
                case UP:
                    moveDir += vec3(0.0f, 1.0f, 0.0f);
                    break;
                case DOWN:
                    moveDir -= vec3(0.0f, 1.0f, 0.0f);
                    break; 
                default:
                    break;
                }

                position += glm::normalize(moveDir) * speed;
            }
    };
};

#endif