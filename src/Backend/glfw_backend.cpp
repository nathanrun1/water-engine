#include "glfw_backend.h"

#include <iostream>
#include <exception>

namespace GLFW {
    GLFWwindow* g_window;
    std::vector<FrameBufferSizeCallback> g_frameBufferSizeCallbacks;
    
    int g_windowWidth = 400;
    int g_windowHeight = 400;

    void _frameBufferSizeCallback(GLFWwindow*, int, int);
    
    
    void init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        g_window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Water", nullptr, nullptr);
        if (!g_window) {
            glfwTerminate();
            throw glfwRuntimeError("Failed to create GLFW window!");
        }
        glfwMakeContextCurrent(g_window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw glfwRuntimeError("Failed to initialize GLAD!");
        }

        glfwSetFramebufferSizeCallback(g_window, _frameBufferSizeCallback);
    }

    void endFrame() {
        glfwSwapBuffers(g_window);
        glfwPollEvents();
    }

    void destroy() {
        glfwTerminate();
    }

    bool windowShouldClose() {
        return glfwWindowShouldClose(g_window);
    }

    GLFWwindow* getWindowPointer() {
        return g_window;
    }

    void setWindowWidth(const int width) {
        g_windowWidth = width;
    }

    void setWindowHeight(const int height) {
        g_windowHeight = height;
    }

    void addFrameBufferSizeCallback(const FrameBufferSizeCallback& callback) {
        g_frameBufferSizeCallbacks.push_back(callback);
    }


    void _frameBufferSizeCallback(GLFWwindow* window, const int width, const int height) {
        for (auto callback : g_frameBufferSizeCallbacks) {
            callback(window, width, height);
        }
    }
}
