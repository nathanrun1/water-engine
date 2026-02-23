#ifndef WATERENGINE_INPUT_H
#define WATERENGINE_INPUT_H

#include <functional>

#include "enums.h"

namespace Input {
    enum class CursorMode {
        GAME,
        GUI
    };
    
    
    typedef std::function<void(double xpos, double ypos)> CursorPosCallback;
    typedef std::function<void(Key key, Action action)> KeyCallback;
    typedef std::function<void(MouseButton mouse_button, Action action)> MouseButtonCallback;
    
    /** Appends callback to cursor position change */
    void append_cursor_pos_callback(CursorPosCallback callback);

    /** Appends callback to key input */
    void append_key_callback(KeyCallback callback);
    
    /** Appends callback to mouse button input */
    void append_mouse_button_callback(const MouseButtonCallback& callback);
    
    /** Determine whether a key is currently being pressed */
    bool is_pressed(Key key);
    
    void set_cursor_mode(const CursorMode& cursor_mode);
}

#endif //WATERENGINE_INPUT_H