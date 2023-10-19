#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void) {
    std::cout << "hello word" << std::endl;
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
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}
