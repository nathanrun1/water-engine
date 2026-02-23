#ifndef WATERENGINE_RENDERER_H
#define WATERENGINE_RENDERER_H
#include <map>
#include <memory>

#include "shader_program.h"
#include "assets/materials.h"
#include "assets/meshes.h"
#include "world/transform.h"

namespace Renderer {
    /** Initializes renderer */
    void init();

    /** Starts the frame draw */
    void begin_draw();

    /** Draws the given mesh */
    void draw_mesh(const Assets::Mesh& mesh, const Transform& transform, const Assets::Material& material);

    /** Creates shader program from given shaders and adds it to available program list */
    void create_program(const std::string& programId, const ShaderProgramInfo &programInfo);

    /** Uses the shader program with the given id */
    void use_program(const std::string& programId);
}

#endif //WATERENGINE_RENDERER_H