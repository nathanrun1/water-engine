#include "glfw_input.h"

#include <iostream>
#include <ostream>

#include "glfw_enums.h"

using namespace Input;

namespace GLFW::Input {
    enum class CursorMode {
        GAME,
        GUI
    };
    
    GLFWwindow* g_window;
    std::vector<GlfwCursorPosCallback> g_cursorPosCallbacks;
    std::vector<GlfwKeyCallback> g_keyCallbacks;
    CursorMode g_cursorMode = CursorMode::GAME;
    
    bool g_ignoreCursor = false;

    /* Aggregate cursor position callback */
    void _cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
        if (g_ignoreCursor) return;
        for (GlfwCursorPosCallback& callback : g_cursorPosCallbacks) {
            callback(xpos, ypos);
        }
    }

    /* Aggregate key callback */
    void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (GlfwKeyCallback& callback : g_keyCallbacks) {
            callback(key, scancode, action, mods);
        }
    }

    /* Links input callbacks */
    void _link_callbacks() {
        glfwSetCursorPosCallback(g_window, _cursor_pos_callback);
        glfwSetKeyCallback(g_window, _key_callback);
    }
    
    void _set_cursor_game() {
        g_ignoreCursor = false;
        glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    void _set_cursor_gui() {
        g_ignoreCursor = true;
        glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    
    void set_cursor_mode(const CursorMode& cursor_mode) {
        switch (cursor_mode) {
            case CursorMode::GAME:
                _set_cursor_game();
                return;
            case CursorMode::GUI:
                _set_cursor_gui();
                return;
        }
    }

    void init(GLFWwindow* window) {
        g_window = window;
        _link_callbacks();
        set_cursor_mode(CursorMode::GAME);
    }

    void append_cursor_pos_callback(GlfwCursorPosCallback callback) {
        g_cursorPosCallbacks.push_back(callback);
    }

    void append_key_callback(GlfwKeyCallback callback) {
        g_keyCallbacks.push_back(callback);
    }

    bool is_pressed(int key) {
        return glfwGetKey(g_window, key) == GLFW_PRESS;
    }
}
