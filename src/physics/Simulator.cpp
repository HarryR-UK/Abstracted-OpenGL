#include "Simulator.h"


namespace ge
{
    Simulator::Simulator()
    {
        m_subStepNumber = 8;
    }

    void Simulator::initialise()
    {
        setupConstraint();
        for(int i = 0; i < 1; ++i)
        {
            VerletObject obj;
            obj.setup("./Resources/Models/Sphere/sphere.obj", 1, vec3(0));
            m_objects.push_back(obj);
        }
    }

    void Simulator::setupConstraint()
    {
        m_constraintShader.setShaderSrc("./Resources/Shaders/constraint.vert","./Resources/Shaders/constraint.frag");
        m_constraintShader.setUBOBinding("Camera", ge::CAMERA_UBO_INDEX);
        m_constraintObject.setup("./Resources/Models/Sphere/sphere.obj", m_constraintPosition);
        m_constraintObject.transform.scale = vec3(m_constraintRadius);

    }

    void Simulator::renderConstraint()
    {
        m_constraintObject.DrawPoints(m_constraintShader);
    }

    void Simulator::render(Shader& shader)
    {
        renderConstraint();
        for(auto &obj : m_objects)
        {
            obj.Draw(shader);
        }
    }

    void Simulator::update( float deltaTime )
    {
        m_time+=deltaTime;
        m_deltaTime = deltaTime;
        float subDT = getSubDeltaTime();
        for (int i = {m_subStepNumber}; i > 0; --i)
        {
            //std::cout << m_objects[0].transform.position.y << '\n';
            //m_objects[0].update(subDT);
            updateGravity();
            updateObjects(subDT);
            checkConstraints();
            checkCollisions();

            //ge::Camera::position = m_objects[0].transform.position;
        }


    }

    float Simulator::getSubDeltaTime()
    {
        return m_deltaTime / static_cast<float>(m_subStepNumber);
    }

    void Simulator::updateObjects(float subDeltaTime)
    {
        for(auto &obj : m_objects)
        {
            obj.update(subDeltaTime);
        }
    }

    void Simulator::updateGravity()
    {
        for(auto &obj : m_objects)
        {
            obj.accelerate(-m_gravity);
        }
    }

    void Simulator::checkCollisions()
    {

    }

    void Simulator::checkConstraints()
    {
        for(auto &obj : m_objects)
        {
            vec3 toObj = m_constraintPosition - obj.transform.position;
            float distance = sqrt((obj.transform.position.x * obj.transform.position.x) + (obj.transform.position.y * obj.transform.position.y) + (obj.transform.position.z * obj.transform.position.z));
            if(distance > (m_constraintRadius - obj.radius))
            {
                vec3 n = toObj / distance;
                obj.transform.position = m_constraintPosition - n * (m_constraintRadius - obj.radius);
            }
        }
    }

    void Simulator::setWindow(ge::Window* window)
    {
        this->m_window = window;
    }

} // namespace ge
