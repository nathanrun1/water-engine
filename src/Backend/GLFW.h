#ifndef WATERENGINE_GLFW_H
#define WATERENGINE_GLFW_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <functional>
#include <stdexcept>

namespace GLFW {
    /* Runtime error related to GLFW backend */
    class glfwRuntimeError : public std::runtime_error {
    public:
        explicit glfwRuntimeError(const std::string& msg) : std::runtime_error(msg) {}
    };


    typedef std::function<void(GLFWwindow*, int, int)> FrameBufferSizeCallback;
    
    /* Initialize GLFW window and state */
    void init();

    /* To be invoked when current frame is ready to be displayed */
    void endFrame();

    /* De-initialize GLFW window and state */
    void destroy();

    /* Determines whether the current window instance should close */
    bool windowShouldClose();

    /* Retrieve pointer to GLFW window instance */
    GLFWwindow* getWindowPointer();

    /* Sets width of window, has no effect after Init() */
    void setWindowWidth(int width);

    /* Sets height of window, has no effect after Init() */
    void setWindowHeight(int height);

    /* Attaches a frame buffer size callback */
    void addFrameBufferSizeCallback(const FrameBufferSizeCallback &callback);
}

#endif //WATERENGINE_GLFW_H