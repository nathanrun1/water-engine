#include "materials.h"

#include <iostream>
#include <unordered_set>
#include <vector>

namespace Assets {
    std::vector<Texture2D> g_maps;
    /* Maps material map (Texture2D) id to its index in the map array, if it has been used in material creation. */
    std::unordered_map<unsigned int, unsigned int> g_map_loc;
    
    /* Validates maps given for the creation of a material. Throws a material_error if any of the maps do not match
     * the dimensions of already-uploaded maps.
     */
    void _validate_map_dimensions(const MaterialInfo& material_info) {
        for (const Texture2D& map : {material_info.albedo_map, material_info.roughness_map, material_info.metallic_map, material_info.normal_map}) {
            if (!map.same_dimensions(MATERIAL_MAP_WIDTH, MATERIAL_MAP_HEIGHT, MATERIAL_MAP_N_CHANNELS))
                throw material_error("Material map dimension mismatch!");
        }
    }
    
    unsigned int _save_map(const Texture2D& material_map) {
        if (g_map_loc.contains(material_map.id)) {
            return g_map_loc[material_map.id];
        }
        g_maps.push_back(material_map);
        
        unsigned int loc = g_maps.size() - 1;
        g_map_loc[material_map.id] = loc;
        return loc;
    }
    
    Material create_material(const MaterialInfo& material_info) {
        _validate_map_dimensions(material_info);
        std::cout << "flags: " << static_cast<uint32_t>(material_info.flags) << std::endl;
        return Material{
            _save_map(material_info.albedo_map),
            _save_map(material_info.roughness_map),
            _save_map(material_info.metallic_map),
            _save_map(material_info.normal_map),
            material_info.albedo_scale,
            material_info.roughness_scale,
            material_info.metallic_scale,
            material_info.flags
        };
    }

    std::span<const Texture2D> get_all_material_maps() {
        return std::span(g_maps);
    }
}
