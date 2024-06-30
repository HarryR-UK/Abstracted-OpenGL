#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Time.h"
#include "Model.h"
#include "Shader.h"
#include "Global.h"
#include "SkyBox.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Framebuffer.h"
#include "physics/Simulator.h"

#include <glm/glm.hpp>
#include <string>
#include <sstream>
#include <vector>


namespace ge
{
    class Application
    {
        private:
            ge::Window m_window;
            ge::DirectionalLight m_directionalLight;

            bool m_skyboxActive = false;
            

            std::vector<std::string> m_faces = 
            {
                "./Resources/Textures/Skybox/skybox/right.jpg",
                "./Resources/Textures/Skybox/skybox/left.jpg",
                "./Resources/Textures/Skybox/skybox/top.jpg",
                "./Resources/Textures/Skybox/skybox/bottom.jpg",
                "./Resources/Textures/Skybox/skybox/front.jpg",
                "./Resources/Textures/Skybox/skybox/back.jpg"
            };

            float m_previousTime = 0.0f;



            Shader m_shader;

            ge::Simulator m_simulator;

            ge::Skybox m_skybox;
            ge::Framebuffer m_screenFrameBuffer;

        private:
            void windowInit();
            void shadersInit();
            void modelsInit();
            void skyboxInit();
            void cameraInit();
            void lightsInit();
            void framebuffersInit();

            void updateShaders();
            void updateLights();
            void updateModels();

        public:

        public:
            Application();
            void update();
            void render();
            void updateWindowFPS();
            void run();
    };
};


#endif // !APPLICATION_H