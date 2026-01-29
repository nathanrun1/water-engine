#ifndef WATERENGINE_SHADER_H
#define WATERENGINE_SHADER_H
#include <string>
#include <stdexcept>

/* Runtime error related to OpenGL shader program initialization */
class shaderProgramRuntimeError : public std::runtime_error {
public:
    explicit shaderProgramRuntimeError(const std::string& msg) : std::runtime_error(msg) {}
};

struct ShaderProgramInfo {
    /* Project-relative path to vertex shader */
    const std::string& vertexPath;
    /* Project-relative path to fragment shader */
    const std::string& fragmentPath;
};

/* Encapulates an OpenGL shader program */
class ShaderProgram {
public:
    ShaderProgram(ShaderProgramInfo& info);

    /* Set this as the active shader program */
    void use();
private:
    unsigned int m_id;
};

#endif //WATERENGINE_SHADER_H