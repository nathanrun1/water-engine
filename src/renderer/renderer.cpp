#include "renderer.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "backend/glfw_backend.h"
#include "renderer/texture2d.h"
#include "renderer/vertex.h"
#include "world/transform.h"
#include "world/world.h"
#include "world/camera/camera.h"

// Cur implementation:
// Single buffer for all models

namespace Renderer {
    std::map<std::string, ShaderProgram> g_availablePrograms;
    ShaderProgram* g_activeProgram;
    unsigned int g_meshVAO;
    unsigned int g_meshVBO;
    unsigned int g_meshEBO;

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
        glGenVertexArrays(1, &g_meshVAO);
        glBindVertexArray(g_meshVAO);

        glGenBuffers(1, &g_meshVBO);
        glBindBuffer(GL_ARRAY_BUFFER, g_meshVBO);

        glGenBuffers(1, &g_meshEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_meshEBO);

        for (const VertexAttributeDesc& desc : Vertex::layout) {
            glVertexAttribPointer(desc.index, desc.size, desc.type, GL_FALSE, sizeof(Vertex), (void*)desc.offset);
            glEnableVertexAttribArray(desc.index);
        }
    }

    /* Loads model data into currently bound VBO and EBO */
    void _load_models() {
        std::span<const Vertex> modelVertices = Assets::get_all_mesh_vertices();
        std::span<const unsigned int> modelIndices = Assets::get_all_mesh_indices();
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * modelVertices.size(), modelVertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * modelIndices.size(), modelIndices.data(), GL_STATIC_DRAW);
    }


    void init() {
        GLFW::add_frame_buffer_size_callback(_frame_buffer_size_callback);

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
    }

    void begin_draw() {
        glm::vec4 bg_color = World::get_main_camera().get_background_color();
        glClearColor(bg_color.r, bg_color.g, bg_color.b, bg_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g_activeProgram->setMat4("u_VP", World::get_main_camera().get_vp_matrix());
    }

    void draw_mesh_with_transform(const Assets::Mesh& model, const Transform& transform) {
        g_activeProgram->setMat4("u_model", transform.get_matrix());


        std::span<const unsigned int> modelIndices = Assets::get_mesh_indices(model);
        size_t indicesOffset = (modelIndices.begin() - Assets::get_all_mesh_indices().begin()) * sizeof(unsigned int);

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
