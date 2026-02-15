#ifndef WATERENGINE_LIGHTING_H
#define WATERENGINE_LIGHTING_H

#include <span>

#include "glm/vec3.hpp"

namespace World {
    enum class LightType {
        Point = 0,
        Directional = 1,
        Ambient = 2
    };

    struct Light {
        glm::vec3 position;
        LightType type;
        glm::vec3 color;
        float intensity;
    };

    void add_light(const Light& light);
    std::span<const Light> get_all_lights();
    
    void set_ambient_light(glm::vec3 color, float intensity);
}

#endif //WATERENGINE_LIGHTING_H