#include "world.h"

#include "backend/glfw_backend.h"

namespace World {
    Camera g_main_camera;
    double g_last_frame_time;

    void init() {
        g_main_camera.transform.position = glm::vec3(0.0, 0.0, 3.0);
        g_last_frame_time = GLFW::get_time();
    }

    FrameContext build_frame_context() {
        float cur_time = GLFW::get_time();
        float delta_time = cur_time - g_last_frame_time;
        g_last_frame_time = cur_time;
        
        return FrameContext{
            delta_time
        };
    }

    const Camera& get_main_camera() {
        return g_main_camera;
    }
}
