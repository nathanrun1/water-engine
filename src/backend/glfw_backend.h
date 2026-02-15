#ifndef WATERENGINE_GLFW_BACKEND_H
#define WATERENGINE_GLFW_BACKEND_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <functional>
#include <stdexcept>

namespace GLFW {
    /* Runtime error related to GLFW backend */
    class glfw_runtime_error : public std::runtime_error {
    public:
        explicit glfw_runtime_error(const std::string& msg) : std::runtime_error(msg) {}
    };


    typedef std::function<void(GLFWwindow*, int, int)> FrameBufferSizeCallback;
    
    /* Initialize GLFW window and state */
    void init();

    /* To be invoked when current frame is ready to be displayed */
    void end_frame();

    /* De-initialize GLFW window and state */
    void destroy();

    /* Determines whether the current window instance should close */
    bool window_should_close();

    /* Sets whether the current window instance should close */
    void set_window_should_close(bool should_close = true);

    /* Retrieve pointer to GLFW window instance */
    GLFWwindow* get_window_ptr();

    void set_window_width(int width);
    int get_window_width();

    void set_window_height(int height);
    int get_window_height();

    /* Calculates the ratio of screen width (x) to height (y) */
    float get_aspect_ratio();

    /* Attaches a frame buffer size callback */
    void add_frame_buffer_size_callback(const FrameBufferSizeCallback &callback);
    
    /* Retrieve amount of seconds since application was launched */
    double get_time();
}

#endif //WATERENGINE_GLFW_BACKEND_H