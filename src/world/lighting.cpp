#include "lighting.h"

namespace World {
    std::vector<Light> g_lights;

    void add_light(const Light &light) {
        g_lights.push_back(light);
    }

    std::span<const Light> get_all_lights() {
        return std::span(g_lights);
    }

}
