#include <pengine/world/world.h>

#include <iostream>

namespace pengine
{
    void World::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        World* world = reinterpret_cast<World*>(glfwGetWindowUserPointer(window));

        world->cameraZ -= yoffset;
    }
}
