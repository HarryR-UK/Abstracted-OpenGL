#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ge
{
    typedef glm::vec3 vec3;
    typedef glm::mat4 mat4;

    class Transform
    {
        private:
            vec3 m_prevPosition = vec3(0.0f);
            vec3 m_prevScale = vec3(1.0f);
            vec3 m_prevRotation = vec3(0.0f);
        private:

        public:
            static inline vec3 s_globalUp = vec3(0.0f, 1.0f, 0.0f);
            static inline vec3 s_globalRight = vec3(1.0f, 0.0f, 0.0f);
            static inline vec3 s_globalForwads = vec3(0.0f, 0.0f, -1.0f);
        public:
            vec3 position = vec3(0.0f);
            vec3 scale = vec3(1.0f);
            vec3 rotation = vec3(0.0f);
            
            vec3 up = vec3(0.0f, 1.0f, 0.0f);
            vec3 right = vec3(1.0f, 0.0f, 0.0f);
            vec3 forwards = vec3(0.0f, 0.0f, -1.0f);
        public:
            mat4 getModelMatrix()
            {
                mat4 modelM = mat4(1.0f);

                //if(position != m_prevPosition)
                //{
                    modelM = glm::translate(modelM, position);
                    m_prevPosition = position;
                //}
                //if(scale != m_prevScale)
                //{
                    modelM = glm::scale(modelM, scale);
                    m_prevScale = scale;
                //}

                //if(rotation != m_prevRotation)
                //{
                    // actual rotation AND calculate the local up down left and right
                    modelM = glm::rotate(modelM, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
                    modelM = glm::rotate(modelM, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
                    modelM = glm::rotate(modelM, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
                

                    m_prevRotation = rotation;
                //}

                return modelM;

            }

    };
};

#endif