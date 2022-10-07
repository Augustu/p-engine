#include <pengine/world/world.h>

namespace pengine
{
    // Is called whenever a key is pressed/released via GLFW
    void World::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        World* world = reinterpret_cast<World*>(glfwGetWindowUserPointer(window));

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        {
            world->cameraX += 0.1f;
        }

        if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        {
            world->cameraX -= 0.1f;
        }

        if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        {
            world->cameraY += 0.1f;
        }

        if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        {
            world->cameraY -= 0.1f;
        }
    }

}