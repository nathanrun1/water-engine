#ifndef WATERENGINE_LIGHTING_H
#define WATERENGINE_LIGHTING_H

#include <span>

#include "glm/vec3.hpp"

namespace World {
    enum class LightType {
        Point,
        Directional
    };

    struct Light {
        glm::vec3 position;
        LightType type;
        glm::vec3 color;
        float intensity;
    };

    void add_light(const Light& light);
    std::span<const Light> get_all_lights();
}

#endif //WATERENGINE_LIGHTING_H