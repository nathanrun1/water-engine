#ifndef WATERENGINE_INPUT_H
#define WATERENGINE_INPUT_H

#include <functional>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GLFW::Input {
    const int KEY_FORWARD = GLFW_KEY_W;
    const int KEY_BACKWARD = GLFW_KEY_S;
    const int KEY_RIGHT = GLFW_KEY_D;
    const int KEY_LEFT = GLFW_KEY_A;
    const int KEY_CLOSE = GLFW_KEY_ESCAPE;

    typedef std::function<void(double, double)> CursorPosCallback;
    typedef std::function<void(int, int, int, int)> KeyCallback;

    /* Initializes the input system */
    void init(GLFWwindow* window);

    /* Handles per-frame update */
    void update();

    /* Determines whether the given key was pressed this frame */
    bool is_pressed(int key);

    /* Appends callback to cursor position change */
    void append_cursor_pos_callback(CursorPosCallback callback);

    /* Appends callback to key input */
    void append_key_callback(KeyCallback callback);
}

#endif //WATERENGINE_INPUT_H