#ifndef WATERENGINE_U_BLOCKS_H
#define WATERENGINE_U_BLOCKS_H
#include "glm/vec3.hpp"
#include "world/lighting.h"

// Structs that include padding to align with the std140 UBO layout
namespace Renderer {
    constexpr size_t MAX_LIGHTS = 8;

    struct alignas(16) UBLight {
        alignas(16) glm::vec3 position;
        alignas(16) glm::vec3 color;
        alignas(4)  unsigned int type;
        alignas(4)  float intensity;
        
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