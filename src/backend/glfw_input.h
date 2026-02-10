#ifndef WATERENGINE_GLFW_INPUT_H
#define WATERENGINE_GLFW_INPUT_H

#include <functional>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "input/enums.h"
#include "input/input.h"

namespace GLFW::Input {
    typedef std::function<void(double xpos, double ypos)> GlfwCursorPosCallback;
    typedef std::function<void(int key, int scancode, int action, int mods)> GlfwKeyCallback;
    typedef std::function<void(int button, int action, int mods)> GlfwMouseButtonCallback;

    /* Initializes the input system */
    void init(GLFWwindow* window);

    /* Determines whether the given key was pressed this frame */
    bool is_pressed(int key);
    
    /* Whether to focus cursor (disable mouse and register cursor pos change callbacks) */
    void set_focus_cursor(bool focus_cursor);

    /* Appends callback to cursor position change */
    void append_cursor_pos_callback(const GlfwCursorPosCallback& callback);

    /* Appends callback to key input */
    void append_key_callback(const GlfwKeyCallback& callback);
    
    /* Appends callback to mouse button input */
    void append_mouse_button_callback(const GlfwMouseButtonCallback& callback);
}

#endif //WATERENGINE_GLFW_INPUT_H