#include "transform.h"

glm::mat4 Transform::get_matrix() const {
    glm::mat4 M = glm::mat4(1.0);
    M = glm::translate(M, position);
    M = M * glm::mat4_cast(rotation);
    M = glm::scale(M, scale);
    return M;
}

void Transform::set_euler_angles(const glm::vec3& angles) {
    rotation = glm::quat(angles);
}
void Transform::set_euler_angles(const float x, const float y, const float z) {
    rotation = glm::quat(glm::vec3(x, y, z));
}

glm::vec3 Transform::get_euler_angles() const {
    return glm::eulerAngles(rotation);
}

