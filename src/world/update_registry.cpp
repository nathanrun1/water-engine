#include "update_registry.h"

#include "world.h"

namespace World::UpdateRegistry {
    std::vector<UpdateCallback> g_update_callbacks;
    
    void add_callback(const UpdateCallback& callback) {
        g_update_callbacks.push_back(callback);
    }
    
    void run_all_callbacks() {
        FrameContext frame_context = build_frame_context();
        for (const UpdateCallback& callback : g_update_callbacks) {
            callback(frame_context);
        }
    }
}
