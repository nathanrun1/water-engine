#include "glfw_input.h"

namespace GLFW::Input {
    GLFWwindow* g_window;
    std::vector<CursorPosCallback> g_cursorPosCallbacks;
    std::vector<KeyCallback> g_keyCallbacks;

    /* Aggregate cursor position callback */
    void _cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
        for (CursorPosCallback& callback : g_cursorPosCallbacks) {
            callback(xpos, ypos);
        }
    }

    /* Aggregate key callback */
    void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (KeyCallback& callback : g_keyCallbacks) {
            callback(key, scancode, action, mods);
        }
    }

    /* Links input callbacks */
    void _link_callbacks() {
        glfwSetCursorPosCallback(g_window, _cursor_pos_callback);
        glfwSetKeyCallback(g_window, _key_callback);
    }

    void init(GLFWwindow* window) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        g_window = window;
        _link_callbacks();
    }

    void append_cursor_pos_callback(CursorPosCallback callback) {
        g_cursorPosCallbacks.push_back(callback);
    }

    void append_key_callback(KeyCallback callback) {
        g_keyCallbacks.push_back(callback);
    }

    bool is_pressed(int key) {
        return glfwGetKey(g_window, key) == GLFW_PRESS;
    }
}