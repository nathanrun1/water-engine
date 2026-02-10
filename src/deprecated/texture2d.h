#ifndef WATERENGINE_TEXTURE2D_H
#define WATERENGINE_TEXTURE2D_H

#include "glad/glad.h"

#include <string>
#include <stdexcept>

class texture_error : public std::runtime_error {
public:
    explicit texture_error(const std::string& msg) : std::runtime_error(msg) {}
};

// TODO: do same with textures as was done with meshes (batching)

/* An 8-bit depth texture, loaded from a given image */
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

#endif //WATERENGINE_TEXTURE2D_H