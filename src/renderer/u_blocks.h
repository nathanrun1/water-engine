#ifndef WATERENGINE_U_BLOCKS_H
#define WATERENGINE_U_BLOCKS_H
#include "glm/vec3.hpp"
#include "world/lighting.h"

// Structs that include padding to align with the std140 UBO layout
namespace Renderer {
    constexpr size_t MAX_LIGHTS = 8;

    struct UBLight {           // alignment            offset    total: 48
        glm::vec3 position;    // 16                   0
        int _p1;
        glm::vec3 color;       // 16                   16
        int _p2;
        unsigned int type;     // 4                    32
        float intensity;       // 4                    36
        int _p3[2];

        UBLight() = default;

        explicit UBLight(const World::Light& light)
            : position{light.position}
            , _p1{}
            , color{light.color}
            , _p2{}
            , type{static_cast<unsigned int>(light.type)}
            , intensity{light.intensity}
            , _p3{}
        {}
    };

    struct UBLighting {              // alignment            offset    total: 400
        int num_lights;              // 4                    0
        UBLight lights[MAX_LIGHTS];  // 384                  4
        int _p[3];
    };
}

#endif //WATERENGINE_U_BLOCKS_H