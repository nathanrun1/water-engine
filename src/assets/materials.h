#ifndef WATERENGINE_MATERIALS_H
#define WATERENGINE_MATERIALS_H
#include <span>

#include "texture2ds.h"
#include "glm/vec3.hpp"

namespace Assets {
    constexpr unsigned int MATERIAL_MAP_WIDTH = 512;
    constexpr unsigned int MATERIAL_MAP_HEIGHT = 512;
    constexpr unsigned int MATERIAL_MAP_N_CHANNELS = 3;
    
    class material_error : public std::runtime_error {
    public:
        explicit material_error(const std::string& msg) : std::runtime_error(msg) {}
    };

    struct Material {
        unsigned int albedo_id;
        unsigned int roughness_id;
        unsigned int metallic_id;
        unsigned int normal_id;
        
        glm::vec3 albedo_scale;
        float roughness_scale;
        float metallic_scale;
    };
    struct MaterialInfo {
        Texture2D albedo_map = white_texture2d(MATERIAL_MAP_WIDTH, MATERIAL_MAP_HEIGHT, MATERIAL_MAP_N_CHANNELS);
        Texture2D roughness_map = white_texture2d(MATERIAL_MAP_WIDTH, MATERIAL_MAP_HEIGHT, MATERIAL_MAP_N_CHANNELS);
        Texture2D metallic_map = white_texture2d(MATERIAL_MAP_WIDTH, MATERIAL_MAP_HEIGHT, MATERIAL_MAP_N_CHANNELS);
        Texture2D normal_map = black_texture2d(MATERIAL_MAP_WIDTH, MATERIAL_MAP_HEIGHT, MATERIAL_MAP_N_CHANNELS);
        
        glm::vec3 albedo_scale = {1.0, 1.0, 1.0};
        float roughness_scale = 1.0;
        float metallic_scale = 0.0;
    };

    Material create_material(const MaterialInfo& material_info);

    std::span<const Texture2D> get_all_material_maps();
}

#endif //WATERENGINE_MATERIALS_H