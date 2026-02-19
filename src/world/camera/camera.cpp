#include "camera.h"

#include <iostream>
#include <ostream>
#include <glm/gtx/io.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "backend/glfw_backend.h"
#include "input/input.h"
#include "world/update_registry.h"

using namespace Input;

Camera::Camera() {
    Input::append_cursor_pos_callback(([&](double xpos, double ypos) {
        m_cursor_pos_callback(xpos, ypos);
    }));
    World::UpdateRegistry::add_callback([&](const World::FrameContext& frame_context) {
        m_update(frame_context);
    });
}

Camera::Camera(const Transform &transform) : Camera() {
    this->transform = transform;
}

glm::mat4 Camera::get_view_matrix() const {
    return inverse(transform.get_matrix());
}

glm::mat4 Camera::get_perp_matrix() const {
    return glm::perspectiveFov(m_fovy, (float)GLFW::get_window_width(), (float)GLFW::get_window_height(), m_near, m_far);
}

glm::mat4 Camera::get_vp_matrix() const {
    return get_perp_matrix() * get_view_matrix();
}

float Camera::get_fovy() const {
    return m_fovy;
}

void Camera::set_background_color(const glm::vec4 &color) {
    m_background_color = color;
}

glm::vec4 Camera::get_background_color() const {
    return m_background_color;
}

void Camera::set_fovy(float fovy) {
    m_fovy = fovy;
}

float d_x_offset;
float d_y_offset;
glm::vec3 d_initial_rot;
glm::vec3 d_after_rot;
void Camera::m_cursor_pos_callback(double xpos, double ypos) {
    if (m_prevCursorX < 0) {
        // Set to initial cursor positions
        m_prevCursorX = xpos;
        m_prevCursorY = ypos;
        return;
    }

    float x_offset = xpos - m_prevCursorX;
    float y_offset = ypos - m_prevCursorY;
    m_prevCursorX = xpos;
    m_prevCursorY = ypos;
    
    glm::vec3 rot = transform.get_euler_angles();

    d_x_offset = x_offset;
    d_y_offset = y_offset;
    d_initial_rot = rot;

    rot.y += -x_offset * m_sensitivity;
    //rot.y = std::fmod(rot.y, glm::radians(360.0f));
    rot.x += -y_offset * m_sensitivity;
    rot.x = std::min(glm::radians(90.0f), std::max(glm::radians(-90.0f), rot.x));
    
    d_after_rot = rot;

    transform.set_euler_angles(rot);
}

void imgui_debug() {
    ImGui::Begin("Camera debug");
    ImGui::Text(("X offset: " + std::to_string(d_x_offset)).c_str());
    ImGui::Text(("Y offset: " + std::to_string(d_y_offset)).c_str());
    ImGui::Text(("Initial rotation" + glm::to_string(d_initial_rot)).c_str());
    ImGui::Text(("Post rotation" + glm::to_string(d_after_rot)).c_str());
    ImGui::End();
}

void Camera::m_update(const World::FrameContext& frame_context) {
    imgui_debug();
    m_update_movement(frame_context.delta_time);
}

void Camera::m_update_movement(const float delta_time) {
    glm::vec4 movement_vector(0.0);
    movement_vector.x += is_pressed(Input::Key::D) ?  1.0 : 0.0;
    movement_vector.x += is_pressed(Input::Key::A) ? -1.0 : 0.0;
    movement_vector.z += is_pressed(Input::Key::W) ? -1.0 : 0.0;
    movement_vector.z += is_pressed(Input::Key::S) ?  1.0 : 0.0;
    
    movement_vector = glm::inverse(get_view_matrix()) * movement_vector;
    //movement_vector = movement_vector.length() >= 0.99f ? glm::normalize(movement_vector) : movement_vector;
    movement_vector *= m_speed * delta_time;
    
    transform.position += glm::xyz(movement_vector);
}


// "Crazy unity type shii"
