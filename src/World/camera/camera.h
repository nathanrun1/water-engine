#ifndef WATERENGINE_CAMERA_H
#define WATERENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world/transform.h"

struct CameraInfo {
    /* Initial position */
    glm::vec3 position;
    /* Initial front direction */
    glm::vec3 front;
    /* Initial up direction */
    glm::vec3 up;

    /* Sensitivity to mouse movement */
    float sensitivity;
    /* Movement speed */
    float speed;
};

struct Camera {
    Camera();
    Camera(Transform& transform);

    /* Generate camera's view matrix */
    glm::mat4 get_view_matrix();
private:
    /* Updates camera's rotation based on new cursor position */
    void m_cursorPosCallback(double xpos, double ypos);

    /* Pitch angle (degrees) */
    float m_pitch = 0.0f;
    /* Yaw angle (degrees) */
    float m_yaw = -90.0f;

    float m_prevCursorX = -1.0f;
    float m_prevCursorY = -1.0f;
    float m_sensitivity;
    float m_speed;

    /* Updates position, front & up vectors based on pitch/yaw angles */
    void m_updateRotation();
};

#endif //WATERENGINE_CAMERA_H