#ifndef WATERENGINE_CAMERA_H
#define WATERENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world/transform.h"

// TODO: refactor derived "FlyCamera" class if we want base class interface for cameras instead of only one type

/* A Camera, representing where and at what perspective the scene is rendered from */
struct Camera {
    Camera();
    Camera(const Transform& transform);

    /* Generate camera's view matrix */
    glm::mat4 get_view_matrix();
    /* Generate camera's perspective matrix */
    glm::mat4 get_perp_matrix();
    /* Generate camera's perspective * view matrix */
    glm::mat4 get_vp_matrix();

    /* Set then camera's background color */
    void set_background_color(const glm::vec4& color);
    /* Retrieve the camera's background color */
    glm::vec4 get_background_color();

    /* Set the camera's vertical FOV, in radians */
    void set_fovy(float fovy);
    /* Retrieves the camera's vertical FOV, in radians */
    float get_fovy();
private:
    Transform m_transform;
    glm::vec4 m_background_color = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    /* Vertical FOV, in radians */
    float m_fovy = glm::radians(90.0f);
    float m_near = 0.1f;
    float m_far = 1000.0f;

    float m_prevCursorX = -1.0f;
    float m_prevCursorY = -1.0f;
    float m_sensitivity;
    float m_speed;

    /* Updates camera's rotation based on new cursor position */
    void m_cursor_pos_callback(double xpos, double ypos);
};

#endif //WATERENGINE_CAMERA_H