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

    /* Initializes the input system */
    void init(GLFWwindow* window);

    /* Determines whether the given key was pressed this frame */
    bool is_pressed(int key);

    /* Appends callback to cursor position change */
    void append_cursor_pos_callback(GlfwCursorPosCallback callback);

    /* Appends callback to key input */
    void append_key_callback(GlfwKeyCallback callback);
}

#endif //WATERENGINE_GLFW_INPUT_H