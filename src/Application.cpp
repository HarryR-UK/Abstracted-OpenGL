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
        
        m_simulator.setWindow(&m_window);
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
        m_window.pollEvents();
        m_window.processInput();
        ge::Camera::updateCameraUBO();
        ge::Camera::getMouseMovement(m_window.getWindow());
        // model transformations
        updateLights();
        updateModels();

        m_simulator.update(ge::Time::deltaTime);
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
        m_simulator.update(ge::Time::deltaTime);
        // m_grassBlock.transform.rotation.y = m_grassBlock.transform.rotation.y + (20 * ge::Time::deltaTime);

    }


    void Application::render()
    {
        m_screenFrameBuffer.listenToRenderCalls();
        m_window.clear(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);

        glStencilMask(0xFF);

        if(m_skyboxActive)
        {
            m_skybox.use();
            m_skybox.Draw();
        }
        

        m_shader.use();
        m_simulator.render(m_shader);


        m_screenFrameBuffer.renderFramebufferToScreen();

        m_window.display();

    }

    void Application::run()
    {
        m_simulator.initialise();
        while(m_window.isOpen())
        {
            ge::Time::currentFrameTime = SDL_GetTicks();
            ge::Time::deltaTime = (ge::Time::currentFrameTime - ge::Time::lastFrameTime) * 0.001;
            update();

            render();


            //updateWindowFPS();
            ge::Time::lastFrameTime = ge::Time::currentFrameTime;
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