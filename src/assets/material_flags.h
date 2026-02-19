#ifndef WATERENGINE_MATERIAL_FLAGS_H
#define WATERENGINE_MATERIAL_FLAGS_H
#include <cstdint>

namespace Assets {
    enum class MaterialFlag : std::uint32_t {
        None = 0,
        Unlit = 1
    };
}

consteval void enable_bitmask_ops(Assets::MaterialFlag);

// Bitmask ops not enabled unless include is after, for some reason
#include "utility/bitmask.h"

#endif //WATERENGINE_MATERIAL_FLAGS_H