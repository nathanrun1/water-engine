#include "textures_2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <span>
#include <vector>

namespace Assets {
    struct Texture2DRange {
        std::span<const std::byte> data;
    };

    std::vector<std::byte> g_texture2d_data;
    std::vector<Texture2DRange> g_texture2d_ranges;

    Texture2D create_texture2d(const std::string& texturePath) {
        int width, height, n_channels;
        stbi_set_flip_vertically_on_load(1);
        std::byte* data = reinterpret_cast<std::byte*>(stbi_load(texturePath.c_str(), &width, &height, &n_channels, 0));
        if (!data) {
            stbi_image_free(data);
            throw texture_error("Failed to load texture: " + texturePath);
        }

        Texture2D new_texture2d(
            g_texture2d_ranges.size(),
            width,
            height,
            n_channels
        );

        std::vector<std::byte>::iterator data_begin = g_texture2d_data.end();

        g_texture2d_data.insert(g_texture2d_data.end(), data, data + sizeof(std::byte) * new_texture2d.size());

        Texture2DRange new_texture_range{
            std::span(data_begin, g_texture2d_data.end())
        };
        g_texture2d_ranges[new_texture2d.id] = new_texture_range;

        return new_texture2d;
    }

    const std::byte* get_texture_data(const Texture2D &texture_2d) {
        Texture2DRange range = g_texture2d_ranges[texture_2d.id];
        return range.data.data();
    }
}
