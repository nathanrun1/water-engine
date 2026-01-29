#include "renderer.h"
#include "Backend/glfw_backend.h"

void _frameBufferSizeCallback(GLFWwindow*, int, int);
void _frameBufferSizeCallback(GLFWwindow* _, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void Renderer::init() {
    GLFW::addFrameBufferSizeCallback(_frameBufferSizeCallback);
}

void Renderer::renderMain() {
    glClearColor(1.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
