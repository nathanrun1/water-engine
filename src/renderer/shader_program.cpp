#include "shader_program.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

const std::string parseShader(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw shader_program_error("Failed to open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

ShaderProgram::ShaderProgram(const ShaderProgramInfo &info) {
    const std::string vertexSource = parseShader(info.vertexPath);
    const std::string fragmentSource = parseShader(info.fragmentPath);
    const char* c_str;

    int success;
    std::string infoLog;
    infoLog.resize(512);

    // Vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);  // Create shader object, and retrieves its ID
    c_str = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &c_str, NULL);  // Provide shader object with source code
    glCompileShader(vertexShader);  // Compile the shader object's underlying shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog.data());
        throw shader_program_error("Failed to compile vertex shader at " + info.vertexPath + ". Info log below.\n" + infoLog);
    }

    // Fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    c_str = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &c_str, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog.data());
        throw shader_program_error("Failed to compile fragment shader at " + info.fragmentPath + ". Info log below.\n" + infoLog);
    }

    // Full program
    m_id = glCreateProgram();  // Creates a program object, and retrieves its ID
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);  // Link compiled shaders

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog.data());
        throw shader_program_error("Shader program linking failed! Info log below.\n" + infoLog);
    }

    glDeleteShader(vertexShader);  // Delete now-obsolete shader objects
    glDeleteShader(fragmentShader);
}

void ShaderProgram::use() {
    glUseProgram(m_id);
}

void ShaderProgram::set_int(const std::string &uniform, const int &value) {
    glUniform1i(glGetUniformLocation(m_id, uniform.c_str()), value);
}

void ShaderProgram::set_mat4(const std::string &uniform, const glm::mat4 &value, GLboolean transpose) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, uniform.c_str()), 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::set_uint(const std::string &uniform, const unsigned int &value) {
    glUniform1ui(glGetUniformLocation(m_id, uniform.c_str()), value);
}


unsigned int ShaderProgram::get_id() {
    return m_id;
}

