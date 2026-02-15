#ifndef WATERENGINE_TEXTURE2DS_H
#define WATERENGINE_TEXTURE2DS_H

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

        [[nodiscard]] bool same_dimensions(const Texture2D& other) const {
            return width == other.width
                && height == other.height
                && n_channels == other.n_channels;
        }
        
        [[nodiscard]] bool same_dimensions(const unsigned int width, const unsigned int height, const unsigned int n_channels) const {
            return this->width == width && this->height == height && this->n_channels == n_channels;
        }

        [[nodiscard]] size_t size() const {
            return width * height * n_channels;
        }
    };

    Texture2D create_texture2d(const std::string& texture_path);
    std::span<const std::byte> get_texture_data(const Texture2D& texture_2d);
    Texture2D white_texture2d(int width = 1, int height = 1, int n_channels = 4);
    Texture2D black_texture2d(int width = 1, int height = 1, int n_channels = 4);
}

#endif //WATERENGINE_TEXTURE2DS_H