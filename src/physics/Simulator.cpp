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
    }

    void Simulator::setupConstraint()
    {
        m_constraintShader.setShaderSrc("./Resources/Shaders/constraint.vert","./Resources/Shaders/constraint.frag");
        m_constraintShader.setUBOBinding("Camera", ge::CAMERA_UBO_INDEX);
        m_constraintObject.setup("./Resources/Models/Sphere/sphere.obj", vec3(0.0f));
        m_constraintObject.transform.position = vec3(0.0f, 0.0f, 0.0f);
        m_constraintObject.transform.scale = vec3(m_constraintRadius);

    }

    float Simulator::calculateDistance(vec3 axis)
    {
        return sqrt((axis.x * axis.x) + (axis.y * axis.y) + (axis.z * axis.z));
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
            spawnObjects();
            updateConstraintMatrix();
            updateGravity();
            checkConstraints(subDT);
            checkCollisions();
            updateObjects(subDT);

            //ge::Camera::position = m_objects[0].transform.position;
        }


    }

    void Simulator::spawnObjects()
    {  
        std::cout << "CURRENT BALLS: " << m_currentBalls << '\n';
        m_timeSpawner = SDL_GetTicks64();
        if(m_timeSpawner - m_timeBetween > m_spawnerDelay && m_currentBalls < m_maxBalls)
        {
            ge::VerletObject obj("./Resources/Models/Sphere/sphere.obj",(rand() % 3) + 1.f, vec3(0.0f + (rand() % 5), 0.0f,0.0f+ (rand() % 5)));
            float randomColorX = sin(ge::Time::time);
            randomColorX *= randomColorX;
            float randomColorY = sin(ge::Time::time + 0.3f * 2);
            randomColorY *= randomColorY;
            float randomColorZ = sin(ge::Time::time + 0.6f * 2);
            randomColorZ *= randomColorZ;
            obj.material.diffuse = vec3(randomColorX, randomColorY, randomColorZ);
            obj.material.shininess = 1.0f;
            m_objects.push_back(obj);
            m_timeBetween = m_timeSpawner;
            m_currentBalls++;
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
        for(size_t i = 0; i < m_objects.size(); ++i)
        {
            VerletObject& obj1 = m_objects[i];
            for(size_t j = i + 1; j < m_objects.size(); ++j)
            {
                VerletObject& obj2 = m_objects[j];
                vec3 axis = obj1.transform.position - obj2.transform.position;
                float dist = sqrt((axis.x * axis.x) + (axis.y * axis.y) + (axis.z * axis.z));
                if(dist < obj1.radius + obj2.radius)
                {
                    vec3 norm = axis / dist;

                    float delta = obj1.radius + obj2.radius - dist;
                    norm = norm * vec3((0.5 * delta));
                     
                    obj1.transform.position += norm;
                    obj2.transform.position -= norm;
                }
            }
        }
    }

    void Simulator::updateConstraintMatrix()
    {
        m_constraintObject.transform.rotation.y += 0.3f * ge::Time::deltaTime;
    }

    void Simulator::checkConstraints(float subDT)
    {
        for(auto &obj : m_objects)
        {
            vec3 disp = obj.transform.position - m_constraintObject.transform.position;
            float dist = sqrt((disp.x * disp.x) + (disp.y * disp.y) + (disp.z * disp.z));
            if(dist > (m_constraintRadius - obj.radius))
            {
                vec3 norm = disp / dist;
                norm = norm * (m_constraintRadius - obj.radius);
                obj.transform.position = (m_constraintObject.transform.position + norm);
                //obj.addVelocity(vec3(-obj.friction), subDT);
            }
        }
    }

    void Simulator::setWindow(ge::Window* window)
    {
        this->m_window = window;
    }

} // namespace ge
