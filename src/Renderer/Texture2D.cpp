#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLint _getTextureFormat(int nChannels) {
    switch (nChannels) {
        case 1:
            return GL_RED;
        case 2:
            return GL_RG;
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            throw textureError("Invalid channel count: " + std::to_string(nChannels));
    }
}

Texture2D::Texture2D(const std::string& texturePath, const unsigned int textureUnit) : m_unit{textureUnit} {
    int width, height, nChannels;
    std::byte* data = reinterpret_cast<std::byte*>(stbi_load(texturePath.c_str(), &width, &height, &nChannels, 0));
    if (!data) {
        stbi_image_free(data);
        throw textureError("Failed to load texture: " + texturePath);
    }

    glGenTextures(1, &m_id);  // Generate texture object, get ID
    glActiveTexture(GL_TEXTURE0 + textureUnit);  // Set given texture unit as active
    glBindTexture(GL_TEXTURE_2D, m_id);  // Bind texture object to texture 2D for given unit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);  // Set mirrored wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // When texel:pixel ratio is high (above 1), texture is downscaled/minified, and we decide to use nearest filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // When texel:pixel ratio is low (below 1), texture is upscaled/magnified, and we decide to use bilinear filtering

    GLint textureFormat = _getTextureFormat(nChannels);
    // load data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, _getTextureFormat(nChannels), width, height, 0, _getTextureFormat(nChannels), GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D); // generate mipmaps

    stbi_image_free(data);
}

void Texture2D::bind(const unsigned int unit) {
    m_unit = unit;
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

unsigned int Texture2D::getUnit() {
    return m_unit;
}

