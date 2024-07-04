#include "VerletObject.h"

namespace ge
{
    VerletObject::VerletObject(const char* modelPath, float radius, vec3 startPos)
    {
        setup(modelPath, radius, startPos);
    }

    VerletObject::VerletObject()
    {
        
    }

    void VerletObject::setup(const char* modelPath, float radius, vec3 startPos)
    {
        this->model.setup(modelPath);
        transform.position = startPos;
        this->radius = radius;
        oldPosition = transform.position;
        acceleration = vec3(0.0f);
        mass = radius * 0.5f;
        transform.scale = vec3(radius);
        friction *= (mass * 0.75f);
    }

    void VerletObject::update( float deltaTime )
    {
        vec3 veclocity = transform.position - oldPosition;
        oldPosition = transform.position;

        this->transform.position = this->transform.position + veclocity + (acceleration) * (deltaTime * deltaTime);

        acceleration = vec3(0.0f, 0.0f, 0.0f);
    }

    void VerletObject::setVelocity( vec3 vel, float deltaTime )
    {
        oldPosition =  transform.position - (vel * deltaTime);
    }

    void VerletObject::addVelocity( vec3 vel, float deltaTime )
    {
        oldPosition -= vel * deltaTime;
    }

    void VerletObject::accelerate( vec3 acc )
    {
        acceleration += acc;
    }

    void VerletObject::Draw(Shader& shader)
    {
        shader.use();
        shader.setMat4("u_model", transform.getModelMatrix());
        shader.setVec3("material.diffuse", this->color);
        model.Draw(shader);
    }



};