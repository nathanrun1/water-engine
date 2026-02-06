#ifndef WATERENGINE_OBJECT_H
#define WATERENGINE_OBJECT_H
#include "../assets/meshes.h"

/* A 3D object existing somewhere in the scene */
struct object {
    /* 3D model of the object's appearance */
    const Models& model;

    /* World-space position */
    glm::vec3 position;
};

#endif //WATERENGINE_OBJECT_H