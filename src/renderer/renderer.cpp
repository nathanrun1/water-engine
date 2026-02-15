#include "renderer.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "u_blocks.h"
#include "assets/materials.h"
#include "backend/glfw_backend.h"
#include "deprecated/texture2d.h"
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

    unsigned int g_albedo_array;

    unsigned int g_lightingUBO;

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


    unsigned int _texture_format(int n_channels) {
        switch (n_channels) {
            case 1:
                return GL_RED;
            case 2:
                return GL_RG;
            case 3:
                return GL_RGB;
            default:
                return GL_RGBA;
        }
    }


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

    /* Load model data into currently bound VBO and EBO */
    void _load_models() {
        std::span<const Vertex> modelVertices = Assets::get_all_mesh_vertices();
        std::span<const unsigned int> modelIndices = Assets::get_all_mesh_indices();
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * modelVertices.size(), modelVertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * modelIndices.size(), modelIndices.data(), GL_STATIC_DRAW);
    }

    /* Initializes and binds texture arrays */
    void _init_textures() {
        // Albedo textures
        glGenTextures(1, &g_albedo_array);
        glActiveTexture(GL_TEXTURE0); // Albedos in unit 0 TODO: don't hardcode this
        glBindTexture(GL_TEXTURE_2D_ARRAY, g_albedo_array);
    }

    /* Load texture data */
    void _load_textures() {
        glActiveTexture(GL_TEXTURE0); // Albedos in unit 0 TODO: don't hardcode this

        std::span<const Assets::Texture2D> albedos = Assets::get_all_albedos();

        unsigned int width = albedos[0].width;
        unsigned int height = albedos[0].height;
        unsigned int n_channels = albedos[0].n_channels;
        unsigned int format = _texture_format(n_channels);
        
        
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height,
            albedos.size(), 0, format, GL_UNSIGNED_BYTE, nullptr);
        for (size_t mat = 0; mat < albedos.size(); ++mat) {
            const std::byte* data = Assets::get_texture_data(albedos[mat]).data();
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, mat, width, height, 1,
                format, GL_UNSIGNED_BYTE, data);
        }

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);  // Set mirrored wrapping
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // When texel:pixel ratio is high (above 1), texture is downscaled/minified, and we decide to use nearest filtering
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // When texel:pixel ratio is low (below 1), texture is upscaled/magnified, and we decide to use bilinear filtering
    }

    /* Initializes lighting buffers */
    void _init_lights() {
        glGenBuffers(1, &g_lightingUBO);
    }

    /* Load lighting data */
    void _load_lights() {
        UBLighting lighting_block;
        std::span<const World::Light> lights = World::get_all_lights();
        for (int i = 0; i < lights.size(); ++i) {
            std::cout << "loading light " << i << '\n';
            lighting_block.lights[i] = UBLight(lights[i]);
        }
        lighting_block.num_lights = lights.size();


        glBindBuffer(GL_UNIFORM_BUFFER, g_lightingUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(UBLighting), &lighting_block, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, g_lightingUBO);  // bind the UBO to UBO binding 0, referred to in shader with `binding = 0`
    }


    void init() {
        GLFW::add_frame_buffer_size_callback(_frame_buffer_size_callback);

        ShaderProgramInfo spInfo{
            "res/shaders/basic.vert",
            "res/shaders/basic.frag"
        };
        create_program("basic", spInfo);
        use_program("basic");

        _init_model_buffers();
        _load_models();

        _init_textures();
        _load_textures();
        
        _init_lights();
        _load_lights();
        
        glEnable(GL_DEPTH_TEST);
    }

    void begin_draw() {
        glm::vec4 bg_color = World::get_main_camera().get_background_color();
        glClearColor(bg_color.r, bg_color.g, bg_color.b, bg_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g_activeProgram->set_mat4("uVP", World::get_main_camera().get_vp_matrix());
    }

    void draw_mesh(const Assets::Mesh& mesh, const Transform& transform, const Assets::Material& material) {
        g_activeProgram->set_mat4("uModel", transform.get_matrix());
        g_activeProgram->set_uint("uMaterial", material.id);

        std::span<const unsigned int> modelIndices = Assets::get_mesh_indices(mesh);
        size_t indicesOffset = (modelIndices.begin() - Assets::get_all_mesh_indices().begin()) * sizeof(unsigned int);

        glDrawElements(GL_TRIANGLES, modelIndices.size(), GL_UNSIGNED_INT, (void*)(indicesOffset));
    }

    void create_program(const std::string &programId, const ShaderProgramInfo &programInfo) {
        g_availablePrograms.emplace(programId, ShaderProgram(programInfo));
    }

    void use_program(const std::string &programId) {
        try {
            ShaderProgram& program = g_availablePrograms.at(programId);
            program.use();
            g_activeProgram = &program;
        } catch (std::out_of_range&) {
            throw std::runtime_error("No shader program of id: " + programId);
        }
    }
}
