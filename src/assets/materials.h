#ifndef WATERENGINE_MATERIALS_H
#define WATERENGINE_MATERIALS_H
#include <span>

#include "textures_2d.h"

namespace Assets {
    class material_error : public std::runtime_error {
    public:
        explicit material_error(const std::string& msg) : std::runtime_error(msg) {}
    };

    struct Material {
        unsigned int id;
    };

    Material create_material(const Texture2D& albedo);

    Texture2D get_albedo(const Material& mat);

    std::span<const Texture2D> get_all_albedos();
}

#endif //WATERENGINE_MATERIALS_H