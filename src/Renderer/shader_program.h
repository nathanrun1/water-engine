#ifndef WATERENGINE_SHADERPROGRAM_H
#define WATERENGINE_SHADERPROGRAM_H
#include <string>
#include <stdexcept>

#include "glad/glad.h"
#include "glm/glm.hpp"

/* Runtime error related to OpenGL shader program initialization */
class shader_program_error : public std::runtime_error {
public:
    explicit shader_program_error(const std::string& msg) : std::runtime_error(msg) {}
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
    ShaderProgram(const ShaderProgramInfo& info);

    /* Set this as the active shader program */
    void use();

    /* Set the value of an integer uniform. Program must be currently in use. */
    void setInt(const std::string& uniform, const int& value);

    /* Set the value of a 4x4 matrix uniform. Program must be currently in use. */
    void setMat4(const std::string& uniform, const glm::mat4& value, const GLboolean transpose = GL_FALSE);

    /* Retrieve the shader program's id */
    unsigned int getId();
private:
    unsigned int m_id;
};

#endif //WATERENGINE_SHADERPROGRAM_H