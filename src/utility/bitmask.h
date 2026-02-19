#ifndef WATERENGINE_BITMASK_H
#define WATERENGINE_BITMASK_H

#include <type_traits>

template<typename E>
concept BitmaskEnum = std::is_enum_v<E> && requires (E e)
{
    enable_bitmask_ops(e);
};

template<BitmaskEnum E>
E operator|(E a, E b) {
    return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) | static_cast<std::underlying_type_t<E>>(b));
}
template<BitmaskEnum E>
E& operator|=(E& a, const E& b) {
    a = static_cast<E>(static_cast<std::underlying_type_t<E>>(a) | static_cast<std::underlying_type_t<E>>(b));
    return a;
}

#endif //WATERENGINE_BITMASK_H