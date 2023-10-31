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
};