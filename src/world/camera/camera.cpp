#include "camera.h"

#include "backend/glfw_backend.h"
#include "backend/glfw_input.h"

Camera::Camera() {
    GLFW::Input::append_cursor_pos_callback(([&](double xpos, double ypos) {
        m_cursor_pos_callback(xpos, ypos);
    }));
}

Camera::Camera(const Transform &transform) : Camera() {
    m_transform = transform;
}

glm::mat4 Camera::get_view_matrix() {
    return inverse(m_transform.get_matrix());
}

glm::mat4 Camera::get_perp_matrix() {
    return glm::perspectiveFov(m_fovy, (float)GLFW::get_window_width(), (float)GLFW::get_window_height(), m_near, m_far);
}

glm::mat4 Camera::get_vp_matrix() {
    return get_perp_matrix() * get_view_matrix();
}

float Camera::get_fovy() {
    return m_fovy;
}

void Camera::set_background_color(const glm::vec4 &color) {
    m_background_color = color;
}

glm::vec4 Camera::get_background_color() {
    return m_background_color;
}

void Camera::set_fovy(float fovy) {
    m_fovy = fovy;
}

void Camera::m_cursor_pos_callback(double xpos, double ypos) {
    if (m_prevCursorX < 0) {
        // Set to initial cursor positions
        m_prevCursorX = xpos;
        m_prevCursorY = ypos;
        return;
    }

    float xOffset = xpos - m_prevCursorX;
    float yOffset = ypos - m_prevCursorY;
    m_prevCursorX = xpos;
    m_prevCursorY = ypos;

    glm::vec3 rot = m_transform.get_euler_angles();

    rot.y += xOffset * m_sensitivity;
    rot.y = std::fmod((rot.y + 360.f), 360.f);
    rot.x += -yOffset * m_sensitivity;
    rot.x = std::min(90.0f, std::max(-90.0f, rot.x));

    m_transform.set_euler_angles(rot);
}









