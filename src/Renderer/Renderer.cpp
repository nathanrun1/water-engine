#include "Renderer.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "Texture2D.h"
#include "Vertex.h"
#include "Backend/GLFW.h"

namespace Renderer {
    std::map<std::string, ShaderProgram> g_availablePrograms;
    ShaderProgram* g_activeProgram;

    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}}
    };

    std::vector<unsigned int> indices = {
        2, 0, 1,
        2, 1, 3
    };

    void _frameBufferSizeCallback(GLFWwindow* _, const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    void init() {
        GLFW::addFrameBufferSizeCallback(_frameBufferSizeCallback);

        ShaderProgramInfo spInfo{
            "res/shaders/basic.vert",
            "res/shaders/basic.frag"
        };
        createProgram("basic", spInfo);
        useProgram("basic");

        Texture2D texContainer("res/textures/container.jpg", 0);
        Texture2D texSmily("res/textures/awesomeface.png", 1);

        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);  // Generates vertex array object. This encodes bound VBOs and attribute configurations
        glBindVertexArray(VAO);        // Bind it as the current VAO

        glGenBuffers(1, &VBO);       // Generates buffer, puts buffer ID into VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Binds our new VBO buffer to the GL_ARRAY_BUFFER target
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);  // Writes data to the buffer bound to GL_ARRAY_BUFFER (i.e. our VBO)
        // GL_STATIC_DRAW specifies STATIC (modified once, used many times) and DRAW (contents modified by application, used as source for drawing)

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        // Specify how vertex data is interpreted. For attr 0: 3 values of type float, non-normalized, with a stride of 3 * float size in memory, offset of 0 in VBO
        // Basically, will interpret each block of 3 values starting at every memory addr of (3 * sizeof(float)) byte stride starting from offset 0 in the array.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vertex::position));
        glEnableVertexAttribArray(0);  // Tell OpenGL shaders are allowed to use this attribute
        glEnableVertexAttribArray(1);
    }

    void renderMain() {
        glm::mat4 transform = glm::mat4(1.0);
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
        g_activeProgram->setMat4("transform", transform);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    }

    void createProgram(const std::string &programId, const ShaderProgramInfo &programInfo) {
        g_availablePrograms.emplace(programId, std::move(ShaderProgram(programInfo)));
    }

    void useProgram(const std::string &programId) {
        try {
            ShaderProgram& program = g_availablePrograms.at(programId);
            program.use();
            g_activeProgram = &program;
        } catch (std::out_of_range) {
            throw std::runtime_error("No shader program of id: " + programId);
        }
    }
}
