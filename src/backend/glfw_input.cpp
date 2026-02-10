#include "glfw_input.h"

#include <iostream>
#include <ostream>

#include "glfw_enums.h"

using namespace Input;

namespace GLFW::Input {
    GLFWwindow* g_window;
    std::vector<GlfwCursorPosCallback> g_cursor_pos_callbacks;
    std::vector<GlfwKeyCallback> g_key_callbacks;
    std::vector<GlfwMouseButtonCallback> g_mouse_button_callbacks;
    bool g_ignoreCursor = false;

    /* Aggregate cursor position callback */
    void _cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
        if (g_ignoreCursor) return;
        for (GlfwCursorPosCallback& callback : g_cursor_pos_callbacks) {
            callback(xpos, ypos);
        }
    }

    /* Aggregate key callback */
    void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (GlfwKeyCallback& callback : g_key_callbacks) {
            callback(key, scancode, action, mods);
        }
    }
    
    void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        for (GlfwMouseButtonCallback& callback : g_mouse_button_callbacks) {
            callback(button, action, mods);
        }
    }

    /* Links input callbacks */
    void _link_callbacks() {
        glfwSetCursorPosCallback(g_window, _cursor_pos_callback);
        glfwSetKeyCallback(g_window, _key_callback);
        glfwSetMouseButtonCallback(g_window, _mouse_button_callback);
    }
    
    void init(GLFWwindow* window) {
        g_window = window;
        _link_callbacks();
    }

    void append_cursor_pos_callback(const GlfwCursorPosCallback& callback) {
        g_cursor_pos_callbacks.push_back(callback);
    }

    void append_key_callback(const GlfwKeyCallback& callback) {
        g_key_callbacks.push_back(callback);
    }

    void append_mouse_button_callback(const GlfwMouseButtonCallback& callback) {
        g_mouse_button_callbacks.push_back(callback);
    }

    bool is_pressed(int key) {
        return glfwGetKey(g_window, key) == GLFW_PRESS;
    }

    void set_focus_cursor(bool focus_cursor) {
        g_ignoreCursor = !focus_cursor;
        glfwSetInputMode(g_window, GLFW_CURSOR, focus_cursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
}
