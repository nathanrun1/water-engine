#include "textures_2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>
#include <vector>

namespace Assets {
    struct Texture2DRange {
        std::span<const std::byte> data;
    };

    std::vector<std::byte> g_texture2d_data;
    std::vector<Texture2DRange> g_texture2d_ranges;

    Texture2D create_texture2d(const std::string& texture_path) {
        int width, height, n_channels;
        stbi_set_flip_vertically_on_load(1);
        auto data = reinterpret_cast<std::byte*>(stbi_load(texture_path.c_str(), &width, &height, &n_channels, 0));
        if (!data) {
            stbi_image_free(data);
            throw texture_error("Failed to load texture: " + texture_path);
        }

        Texture2D new_texture2d(
            g_texture2d_ranges.size(),
            width,
            height,
            n_channels
        );

        size_t data_offset = g_texture2d_data.size();
        
        g_texture2d_data.reserve(g_texture2d_data.size() + new_texture2d.size() + 1);
        g_texture2d_data.insert(g_texture2d_data.end(), data, data + new_texture2d.size());
        
        std::span full_data_span(g_texture2d_data);
        Texture2DRange new_texture_range{full_data_span.subspan(data_offset, new_texture2d.size())};
        g_texture2d_ranges.push_back(new_texture_range);

        return new_texture2d;
    }

    std::span<const std::byte> get_texture_data(const Texture2D &texture_2d) {
        std::cout << g_texture2d_ranges.size() << " ranges, id: " <<  texture_2d.id << std::endl;
        auto& [data] = g_texture2d_ranges[texture_2d.id];
        return data;
    }
}

// "Nightmare difficulty bug"
