#include "StaticObject.h"


namespace ge
{
    void StaticObject::setup(const char* modelPath, vec3 startPos)
    {
        this->model.setup(modelPath);
        transform.position = startPos;
    }

    void StaticObject::Draw(Shader& shader)
    {
        shader.use();
        shader.setMat4("u_model", this->transform.getModelMatrix());
        this->model.Draw(shader);
    }
    void StaticObject::DrawPoints(Shader& shader)
    {
        shader.use();
        shader.setMat4("u_model", this->transform.getModelMatrix());
        this->model.DrawPoints(shader);
    }
}