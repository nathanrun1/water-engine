#ifndef WATERENGINE_TEXTURES_H
#define WATERENGINE_TEXTURES_H

#include <span>
#include <string>
#include <stdexcept>

namespace Assets {
    class texture_error : public std::runtime_error {
    public:
        explicit texture_error(const std::string& msg) : std::runtime_error(msg) {}
    };

    struct Texture2D {
        unsigned int id;
        unsigned int width;
        unsigned int height;
        unsigned int n_channels;

        inline bool same_dimensions(const Texture2D& other) {
            return width == other.width
                && height == other.height
                && n_channels == other.n_channels;
        }

        inline size_t size() {
            return width * height * n_channels;
        }
    };

    Texture2D create_texture2d(const std::string& texture_path);

    std::span<const std::byte> get_texture_data(const Texture2D& texture_2d);
}

#endif //WATERENGINE_TEXTURES_H