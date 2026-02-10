#ifndef WATERENGINE_WORLD_H
#define WATERENGINE_WORLD_H
#include "world/camera/camera.h"
#include "world/frame_context.h"

namespace World {
    void init();
    FrameContext build_frame_context();
    const Camera& get_main_camera();
}

#endif //WATERENGINE_WORLD_H