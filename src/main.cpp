#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "shader.h"

void OnFrameBufferSizeChange(GLFWwindow* window, int width, int height) {
    std::cout << "Frame buffer size changed : " << width << " x " << height << std::endl;
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Render() {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(void) {
    if (!glfwInit()) {
        const char *description;
        glfwGetError(&description);
        std::cout << description << std::endl;
        return -1;
    }

    //TODO: what is forward compatible core profile?
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {
        const char *description;
        glfwGetError(&description);
        std::cout << description << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "fail to init glad" << std::endl;
        glfwTerminate();
        return -1;
    }
    auto glVersion = glGetString(GL_VERSION);
    std::cout << "opengl version: " << glVersion << std::endl;

    // init viewport
    OnFrameBufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFrameBufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    auto vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    auto fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    std::cout << "vertex shader id : " << vertexShader->Get() << std::endl;
    std::cout << "fragment shader id : " << fragmentShader->Get() << std::endl;

    while (!glfwWindowShouldClose(window)) {
        Render();
        // exchange front and back buffer
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}
