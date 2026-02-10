#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "renderer/renderer.h"
#include "backend/glfw_backend.h"
#include "backend/glfw_input.h"
#include "input/enums.h"
#include "world/transform.h"
#include "world/update_registry.h"
#include "world/world.h"

// TO IMPLEMENT:
// - Load from .obj
// X Geometry batching
//   - Vertex deduplication
// - Instancing

using namespace Input;

Vertex cubeVertices[] = {
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f, -0.5f},  { 0.0f, 1.0f}}
};

unsigned int cubeIndices[] = {
     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

void key_callback(Key key, Action action) {
    if (key == Key::Escape && action == Action::Press) {
        GLFW::Input::set_focus_cursor(false);
    }
}

void mouse_callback(MouseButton mouse_button, Action action) {
    if (!ImGui::GetIO().WantCaptureMouse && mouse_button == MouseButton::M1 && action == Action::Press)
        GLFW::Input::set_focus_cursor(true);
}

int main() {
    GLFW::set_window_width(1600);
    GLFW::set_window_height(1200);
    GLFW::init();
    
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(GLFW::get_window_ptr(), true);
    ImGui_ImplOpenGL3_Init();
    
    Input::set_cursor_mode(CursorMode::GAME);
    Input::append_key_callback(key_callback);
    Input::append_mouse_button_callback(mouse_callback);

    std::vector<Vertex> vertices(std::begin(cubeVertices), std::end(cubeVertices));
    std::vector<unsigned int> indices(std::begin(cubeIndices), std::end(cubeIndices));
    Assets::Mesh cube = Assets::create_mesh(vertices, indices);
    
    World::init();
    Renderer::init();
    
    while (!GLFW::window_should_close()) {
        Renderer::begin_draw();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        
        for (glm::vec3& pos : cubePositions) {
            World::UpdateRegistry::run_all_callbacks();
            Transform transform;
            transform.position = pos;
            transform.set_euler_angles(0.0f, glfwGetTime() * glm::radians(90.0f), 0.0f);
            transform.scale = glm::vec3(2.0f, 1.0f, 1.0f);
            Renderer::draw_mesh_with_transform(cube, transform);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        GLFW::end_frame();
    }
    GLFW::destroy();
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}