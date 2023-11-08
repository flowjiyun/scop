#pragma once

#include "common.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

CLASS_PTR(Context)
class Context {
    public:
        static ContextUPtr Create();
        void Render();
        void ProcessInput(GLFWwindow* window);
        void Reshape(uint32_t width, uint32_t height);
        void MoveMouse(double x, double y);
        void ClickMouseButton(int button, int aciton, double x, double y);


    private:
        Context() = default;
        bool Init();
        ProgramUPtr m_program;
        ProgramUPtr m_simpleProgram;
        VertexLayoutUPtr m_vertexLayout;
        BufferUPtr m_vertextBuffer;
        BufferUPtr m_indexBuffer;
        TextureUPtr m_texture;
        TextureUPtr m_texture2;

        //camera
        glm::vec3 m_cameraPos {glm::vec3(0.0f, 0.0f, 3.0f)};
        glm::vec3 m_cameraFront {glm::vec3(0.0f, 0.0f, -1.0f)};
        glm::vec3 m_cameraUp {glm::vec3(0.0f, 1.0f, 0.0f)};
        float m_cameraPitch {0.0f};
        float m_cameraYaw {0.0f};

        //mouse
        bool m_isCameraControlEnabled {false};
        glm::vec2 m_mousePos {glm::vec2(0.0f)};

        //window size
        uint32_t m_windowWidth {WINDOW_WIDTH};
        uint32_t m_windowHeight {WINDOW_HEIGHT};
        glm::vec4 m_clearColor {glm::vec4(0.1f, 0.2f, 0.3f, 0.0f)};

        // object
        glm::vec3 m_objectColor {glm::vec3(1.0f, 0.5f, 0.0f)};

        // light
        struct Light {
            glm::vec3 position { glm::vec3(3.0f, 3.0f, 3.0f) };
            glm::vec3 ambient { glm::vec3(0.1f, 0.1f, 0.1f) };
            glm::vec3 diffuse { glm::vec3(0.5f, 0.5f, 0.5f) };
            glm::vec3 specular { glm::vec3(1.0f, 1.0f, 1.0f) };
        };
        Light m_light;

        //material
        struct Material {
            TextureUPtr diffuse;
            TextureUPtr specular;
            float shininess { 32.0f };
        };
        Material m_material;

        //animation
        bool m_isAnimationEnabled {true};
};