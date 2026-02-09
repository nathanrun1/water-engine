#ifndef WATERENGINE_KEYS_H
#define WATERENGINE_KEYS_H

#include <unordered_map>

namespace Input {
    enum class Key {
        Unknown,

        // Printable keys
        Space,
        Apostrophe,   // '
        Comma,        // ,
        Minus,        // -
        Period,       // .
        Slash,        // /
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Semicolon,    // ;
        Equal,        // =

        A, B, C, D, E, F, G,
        H, I, J, K, L, M, N,
        O, P, Q, R, S, T, U,
        V, W, X, Y, Z,

        LeftBracket,  // [
        Backslash,    // '\'
        RightBracket, // ]
        GraveAccent,  // `
        World1,
        World2,

        // Function / control keys
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,

        F1,  F2,  F3,  F4,  F5,
        F6,  F7,  F8,  F9,  F10,
        F11, F12, F13, F14, F15,
        F16, F17, F18, F19, F20,
        F21, F22, F23, F24, F25,

        // Keypad
        KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,
        KPEqual,

        // Modifiers
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,
    };
}

namespace std {
    template<>
    struct hash<Input::Key> {
        std::size_t operator()(Input::Key k) const noexcept {
            return static_cast<std::size_t>(k);
        }
    };
}



#endif //WATERENGINE_KEYS_H