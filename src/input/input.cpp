#include "input.h"

#include <iostream>
#include <ostream>

#include "backend/glfw_enums.h"
#include "backend/glfw_input.h"

namespace Input {
    void append_cursor_pos_callback(CursorPosCallback callback) {
        GLFW::Input::append_cursor_pos_callback(callback);
    }
    
    void append_key_callback(KeyCallback callback) {
        GLFW::Input::append_key_callback([&](int key, int scancode, int action, int mods) {
            std::cout  << "cursor pos" << std::endl;
            callback(from_glfw_key.at(key), from_glfw_action.at(action));
        });
    }

    bool is_pressed(Key key) {
        return GLFW::Input::is_pressed(to_glfw_key.at(key));
    }
}
