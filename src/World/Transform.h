#ifndef WATERENGINE_TRANSFORM_H
#define WATERENGINE_TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/gtx/quaternion.hpp"

struct Transform {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat rotation = glm::identity<glm::quat>();
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    /* Constructs a model matrix corresponding to this transform */
    glm::mat4 get_matrix() const;

    /* Set rotation euler angles, in radians */
    void set_euler_angles(const glm::vec3& angles);
    /* Set rotation euler angles, in radians */
    void set_euler_angles(const float x, const float y, const float z);

    /* Get rotation euler angles, in radians */
    glm::vec3 get_euler_angles() const;
};

#endif //WATERENGINE_TRANSFORM_H