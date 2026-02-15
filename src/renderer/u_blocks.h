#ifndef WATERENGINE_U_BLOCKS_H
#define WATERENGINE_U_BLOCKS_H
#include "glm/vec3.hpp"
#include "world/lighting.h"

// Structs that include padding to align with the std140 UBO layout
namespace Renderer {
    constexpr size_t MAX_LIGHTS = 8;

    struct alignas(16) UBLight {                       // alignment            offset    total: 40
        alignas(16) glm::vec3 position;    // 16                   0
        alignas(16) glm::vec3 color;       // 16                   16
        alignas(4)  unsigned int type;     // 4                    32
        alignas(4)  float intensity;       // 4                    36
        
        UBLight() = default;

        explicit UBLight(const World::Light& light)
            : position{light.position}
            , color{light.color}
            , type{static_cast<unsigned int>(light.type)}
            , intensity{light.intensity}
        {}
    };

    struct alignas(16) UBLighting {
        alignas(4)  unsigned int num_lights;
        alignas(16) UBLight lights[MAX_LIGHTS];
    };
}

#endif //WATERENGINE_U_BLOCKS_H