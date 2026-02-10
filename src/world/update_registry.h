#ifndef WATERENGINE_UPDATE_REGISTRY_H
#define WATERENGINE_UPDATE_REGISTRY_H
#include <functional>
#include <vector>

#include "world.h"

namespace World::UpdateRegistry {
    typedef std::function<void(const FrameContext&)> UpdateCallback;
    
    /* Adds the given update callback */
    void add_callback(const UpdateCallback& callback);

    /* Runs all added update callbacks */
    void run_all_callbacks();
}

#endif //WATERENGINE_UPDATE_REGISTRY_H