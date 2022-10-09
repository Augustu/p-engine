#ifndef PENGINE_WORLD_H
#define PENGINE_WORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <pengine/world/object/object.h>

#include <string>

namespace pengine
{
    class World
    {
    private:
        int windowWidth;
        int windowHeight;
        std::string windowTitle;

        GLFWwindow* window;

        float focusX;
        float focusY;
        float focusZ;

        GLuint renderingProgram;
        GLuint* vao;
        GLuint* vbo;
        GLuint* ebo;

        std::vector<Object> objects;

        double currentTime;
        std::vector<std::vector<float>*>* objectVertices;

    public:
        float cameraX;
        float cameraY;
        float cameraZ;


    private:
        void init(GLFWwindow* window);
        void display(GLFWwindow* window, double currentTime);
        void updateObjects(float elapseTime);
        void updateBuffers();

    public:
        World(int windowWidth, int windowHeight, std::string windowTitle,
                float cameraX, float cameraY, float cameraZ);
        ~World();

        int Run();

        // control
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        void SetFocus(float focusX, float focusY, float focusZ);

        void PutObject(Object object);

        void SetupObjects();
        void SetupShaders();
    };

}

#endif