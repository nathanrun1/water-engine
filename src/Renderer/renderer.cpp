#include "renderer.h"

#include "shader.h"
#include "vertex.h"
#include "Backend/glfw_backend.h"

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

void _frameBufferSizeCallback(GLFWwindow*, int, int);
void Renderer::init() {
    GLFW::addFrameBufferSizeCallback(_frameBufferSizeCallback);

    ShaderProgramInfo spInfo{
        "res/shaders/basic.vert",
        "res/shaders/basic.frag"
    };
    ShaderProgram shaderProgram{spInfo};

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

    shaderProgram.use();
}

void Renderer::renderMain() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
}


void _frameBufferSizeCallback(GLFWwindow* _, const int width, const int height) {
    glViewport(0, 0, width, height);
}
