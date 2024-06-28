#include "Application.h"

namespace ge
{
    Application::Application()
    {
        windowInit();
        cameraInit();
        shadersInit();
        modelsInit();
        skyboxInit();
        lightsInit();
        framebuffersInit();
    }


    void Application::windowInit()
    {
        m_window.setupWindow(ge::WINDOW_WIDTH, ge::WINDOW_HEIGHT, "OpenGL TESTING", 3, 3);
    }

    void Application::shadersInit()
    {
        m_shader.setShaderSrc("./Resources/Shaders/main.vert", "./Resources/Shaders/main.frag");
        m_shader.setUBOBinding("Camera", ge::CAMERA_UBO_INDEX);
    }

    void Application::modelsInit()
    {
        m_grassBlock.setup("./Resources/Models/MCCube/GrassBlock.obj");
    }

    void Application::skyboxInit()
    {
        m_skybox.setup(m_faces);
        m_skybox.setUBOBinding("Camera", ge::CAMERA_UBO_INDEX);
    }
    void Application::cameraInit()
    {
        ge::Camera::setup();
    }

    void Application::lightsInit()
    {
        m_shader.use();
        m_shader.setVec3("directionalLight.direction", m_directionalLight.direction);
        m_shader.setVec3("directionalLight.ambient", m_directionalLight.ambient);
        m_shader.setVec3("directionalLight.diffuse", m_directionalLight.diffuse);
        m_shader.setVec3("directionalLight.specular", m_directionalLight.specular);

        m_shader.setFloat("material.shininess", 1);
    }

    void Application::framebuffersInit()
    {
        m_screenFrameBuffer.setup("./Resources/Shaders/Framebuffers/screenFrame.vert", "./Resources/Shaders/Framebuffers/screenFrame.frag");
    }

    void Application::update()
    {
        m_window.processInput();
        ge::Camera::updateCameraUBO();
        // model transformations
        updateLights();
        updateModels();

    }

    void Application::updateLights()
    {
        m_shader.use();
        m_shader.setVec3("directionalLight.direction", m_directionalLight.direction);
        m_shader.setVec3("directionalLight.ambient", m_directionalLight.ambient);
        m_shader.setVec3("directionalLight.diffuse", m_directionalLight.diffuse);
        m_shader.setVec3("directionalLight.specular", m_directionalLight.specular);
        
        m_shader.setFloat("material.shininess", 1);
    }

    void Application::updateModels()
    {

        m_grassBlock.transform.rotation.y = m_grassBlock.transform.rotation.y + (20 * ge::Time::deltaTime);

    }


    void Application::render()
    {
        m_screenFrameBuffer.listenToRenderCalls();
        m_window.clear(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        if(m_skyboxActive)
        {
            m_skybox.use();
            m_skybox.Draw();
        }
        

        m_shader.use();
        m_grassBlock.Draw(m_shader);


        m_screenFrameBuffer.renderFramebufferToScreen();

        m_window.display();
        m_window.pollEvents();

    }

    void Application::run()
    {
        while(m_window.isOpen())
        {
            update();

            render();

            ge::Time::update();

            updateWindowFPS();
        }
    }

    void Application::updateWindowFPS()
    {
        std::stringstream ss;
        ss<<"OPENGL TESTING -- FPS: " << ge::Time::fps;
        if(ge::Time::time - m_previousTime >= 1.0f)
        {
            m_window.setWindowTitle(ss.str());
            m_previousTime = ge::Time::time;
        }
    }

};