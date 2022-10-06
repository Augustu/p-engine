#include <pengine/world/world.h>

namespace pengine
{
    void World::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        World* world = reinterpret_cast<World*>(window);

        world->cameraZ -= yoffset;
    }
}
