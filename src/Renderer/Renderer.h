#ifndef WATERENGINE_RENDERER_H
#define WATERENGINE_RENDERER_H
#include <map>
#include <memory>

#include "ShaderProgram.h"

namespace Renderer {
    /* Initializes renderer */
    void init();

    /* Renders the main scene */
    void renderMain();

    /* Creates shader program from given shaders and adds it to available program list */
    void createProgram(const std::string& programId, const ShaderProgramInfo &programInfo);

    /* Uses the shader program with the given id */
    void useProgram(const std::string& programId);
}

#endif //WATERENGINE_RENDERER_H