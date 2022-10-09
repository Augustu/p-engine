#include <pengine/world/world.h>

#include <assert.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pengine
{
    World::World(int windowWidth, int windowHeight, std::string windowTitle,
                float cameraX, float cameraY, float cameraZ)
    : windowWidth(windowWidth), windowHeight(windowHeight), windowTitle(windowTitle),
        cameraX(cameraX), cameraY(cameraY), cameraZ(cameraZ)
    {
        assert(windowWidth > 0);
        assert(windowHeight > 0);

        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
        glfwMakeContextCurrent(window);

        glfwSetWindowUserPointer(window, this);

        if (glewInit() != GLEW_OK)
        {
            exit(EXIT_FAILURE);
        }

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);
        glfwSetScrollCallback(window, scroll_callback);

        glfwSwapInterval(1);
        init(window);
    }

    World::~World()
    {
        delete vao;
        delete vbo;
    }

    void World::init(GLFWwindow* window)
    {
        renderingProgram = glCreateProgram();
    }

    void World::display(GLFWwindow* window, double currentTime)
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(renderingProgram);

        double elapseTime = currentTime - this->currentTime;
        this->currentTime = currentTime;

        updateObjects(elapseTime);
        // updateBuffers();

        // get the uniform variables for the MV and projection matrices
        GLuint mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
        GLuint projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

        // build perspective matrix
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        float aspect = (float)windowWidth / (float)windowHeight;
        glm::mat4 pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

        // build view matrix, model matrix, and model-view matrix
        glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(focusX, focusY, focusZ));
        glm::mat4 mvMat = vMat * mMat;

        // copy perspective and MV matrices to corresponding uniform variables
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        for (Object object : objects)
        {
            // glDrawElements(GL_TRIANGLES, object.Indices().size(), GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 0, object.Indices().size());
        }
    }

    int World::Run()
    {
        while (!glfwWindowShouldClose(window)) {
            display(window, glfwGetTime());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    void World::SetFocus(float focusX, float focusY, float focusZ)
    {
        focusX = focusX;
        focusY = focusY;
        focusZ = focusZ;
    }

    void World::PutObject(Object object)
    {
        objects.push_back(object);
    }

    void World::SetupObjects()
    {
        int numOfObjects = objects.size();

        objectVertices = new std::vector<std::vector<float>*>(numOfObjects, NULL);

        vao = new GLuint[numOfObjects];
        vbo = new GLuint[numOfObjects];
        ebo = new GLuint[numOfObjects];

        glGenVertexArrays(numOfObjects, vao);
        glGenBuffers(numOfObjects, vbo);
        glGenBuffers(numOfObjects, ebo);

        for (int i = 0; i < numOfObjects; ++i)
        {
            Object object = objects[i];
            std::vector<Vertex> vertices = object.MeshVertices();
            std::vector<int> indices = object.Indices();

            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

            // ids
            glEnableVertexAttribArray(5);
            glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

            // weights
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
        }
    }

    void World::SetupShaders()
    {
        Object object = objects.at(0);

        GLuint vShader = object.VertShader();
        GLuint fShader = object.FragShader();

        glAttachShader(renderingProgram, vShader);
        glAttachShader(renderingProgram, fShader);
        glLinkProgram(renderingProgram);
    }

    void World::updateObjects(float elapseTime)
    {
        int numOfObjects = objects.size();

        for (int i = 0; i < numOfObjects; ++i)
        {
            objects[i].Update(elapseTime);
        }
    }

    void World::updateBuffers()
    {
        int numOfObjects = objects.size();

        for (int i = 0; i < numOfObjects; ++i)
        {
            glBufferData(GL_ARRAY_BUFFER, (*objectVertices)[i]->size() * sizeof(float), (*objectVertices)[i]->data(), GL_DYNAMIC_DRAW);
        }
    }

}
