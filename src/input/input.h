#ifndef WATERENGINE_INPUT_H
#define WATERENGINE_INPUT_H

#include <functional>

#include "enums.h"

namespace Input {
    typedef std::function<void(double xpos, double ypos)> CursorPosCallback;
    typedef std::function<void(Key key, Action action)> KeyCallback;
    
    /* Appends callback to cursor position change */
    void append_cursor_pos_callback(CursorPosCallback callback);

    /* Appends callback to key input */
    void append_key_callback(KeyCallback callback);
    
    /* Determine whether a key is currently being pressed */
    bool is_pressed(Key key);
}

#endif //WATERENGINE_INPUT_H