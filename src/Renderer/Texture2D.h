#ifndef WATERENGINE_TEXTURE_H
#define WATERENGINE_TEXTURE_H

#include "glad/glad.h"

#include <string>
#include <stdexcept>

class textureError : public std::runtime_error {
public:
    explicit textureError(const std::string& msg) : std::runtime_error(msg) {}
};

/* An 8-bit texture, loaded from a given image */
struct Texture2D {
    Texture2D(const std::string& texturePath, const unsigned int textureUnit = 0);

    /* Binds this texture to the given texture unit */
    void bind(const unsigned int unit);

    /* Retrieve the texture unit that this texture is bound to */
    unsigned int getUnit();
private:
    unsigned int m_id;
    unsigned int m_unit;
};

#endif //WATERENGINE_TEXTURE_H