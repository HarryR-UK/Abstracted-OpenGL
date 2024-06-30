#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#include <glm/glm.hpp>
#include "../Model.h"
#include "../Transform.h"
#include "../Shader.h"

typedef glm::vec3 vec3;
namespace ge
{
    struct StaticObject
    {
        Model model;
        Transform transform;

        void setup(const char* modelPath, vec3 startPos = vec3(0.0f));
        void Draw(Shader& shader);
        void DrawPoints(Shader& shader);

    };
} // namespace ge



#endif // !STATIC_OBJECT_H