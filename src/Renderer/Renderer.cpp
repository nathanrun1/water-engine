#include "renderer.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "texture2d.h"
#include "vertex.h"
#include "backend/glfw_backend.h"
#include "world/transform.h"

// Cur implementation:
// Single buffer for all models

namespace Renderer {
    std::map<std::string, ShaderProgram> g_availablePrograms;
    ShaderProgram* g_activeProgram;
    unsigned int g_modelVAO;
    unsigned int g_modelVBO;
    unsigned int g_modelEBO;

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

    void _frame_buffer_size_callback(GLFWwindow* _, const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    /* Initializes model data VAO, VBO and EBO */
    void _init_model_buffers() {
        glGenVertexArrays(1, &g_modelVAO);
        glBindVertexArray(g_modelVAO);

        glGenBuffers(1, &g_modelVBO);
        glBindBuffer(GL_ARRAY_BUFFER, g_modelVBO);

        glGenBuffers(1, &g_modelEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_modelEBO);

        for (const VertexAttributeDesc& desc : Vertex::layout) {
            glVertexAttribPointer(desc.index, desc.size, desc.type, GL_FALSE, sizeof(Vertex), (void*)desc.offset);
            glEnableVertexAttribArray(desc.index);
        }
    }

    /* Loads model data into currently bound VBO and EBO */
    void _load_models() {
        std::span<const Vertex> modelVertices = Assets::getAllModelVertices();
        std::span<const unsigned int> modelIndices = Assets::getAllModelIndices();
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * modelVertices.size(), modelVertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * modelIndices.size(), modelIndices.data(), GL_STATIC_DRAW);
    }


    void init() {
        GLFW::addFrameBufferSizeCallback(_frame_buffer_size_callback);

        ShaderProgramInfo spInfo{
            "res/shaders/basic.vert",
            "res/shaders/basic.frag"
        };
        create_program("basic", spInfo);
        use_program("basic");

        Texture2D texContainer("res/textures/container.jpg", 0);
        Texture2D texSmily("res/textures/awesomeface.png", 1);

        _init_model_buffers();
        _load_models();
        
        glEnable(GL_DEPTH_TEST);

        // unsigned int VAO, VBO, EBO;
        // glGenVertexArrays(1, &VAO);  // Generates vertex array object. This encodes bound VBOs and attribute configurations
        // glBindVertexArray(VAO);        // Bind it as the current VAO
        //
        // glGenBuffers(1, &VBO);       // Generates buffer, puts buffer ID into VBO
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Binds our new VBO buffer to the GL_ARRAY_BUFFER target
        // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);  // Writes data to the buffer bound to GL_ARRAY_BUFFER (i.e. our VBO)
        // // GL_STATIC_DRAW specifies STATIC (modified once, used many times) and DRAW (contents modified by application, used as source for drawing)
        //
        // glGenBuffers(1, &EBO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
        //
        // // Specify how vertex data is interpreted. For attr 0: 3 values of type float, non-normalized, with a stride of 3 * float size in memory, offset of 0 in VBO
        // // Basically, will interpret each block of 3 values starting at every memory addr of (3 * sizeof(float)) byte stride starting from offset 0 in the array.
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vertex::position));
        // glEnableVertexAttribArray(0);  // Tell OpenGL shaders are allowed to use this attribute
        // glEnableVertexAttribArray(1);
    }

    void begin_draw() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // TODO: change to camera background property
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 V = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -3.0));
        glm::mat4 P = glm::perspective(glm::radians(90.0f), GLFW::getAspectRatio(), 0.1f, 100.0f);
        g_activeProgram->setMat4("u_view", V);
        g_activeProgram->setMat4("u_projection", P);
    }

    void draw_model_with_transform(const Assets::Model& model, const Transform& transform) {
        g_activeProgram->setMat4("u_model", transform.get_matrix());


        std::span<const unsigned int> modelIndices = Assets::getModelIndices(model);
        size_t indicesOffset = (modelIndices.begin() - Assets::getAllModelIndices().begin()) * sizeof(unsigned int);

        glDrawElements(GL_TRIANGLES, modelIndices.size(), GL_UNSIGNED_INT, (void*)(indicesOffset));
    }

    void create_program(const std::string &programId, const ShaderProgramInfo &programInfo) {
        g_availablePrograms.emplace(programId, std::move(ShaderProgram(programInfo)));
    }

    void use_program(const std::string &programId) {
        try {
            ShaderProgram& program = g_availablePrograms.at(programId);
            program.use();
            g_activeProgram = &program;
        } catch (std::out_of_range) {
            throw std::runtime_error("No shader program of id: " + programId);
        }
    }
}
