#include <pengine/world/world.h>

#include <assert.h>
#include <iostream>

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
        // TODO
        // renderingProgram = createShaderProgram(vertShaderPath, fragShaderPath);
        // cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
        // cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // shift down Y to reveal perspective

    }

    void World::display(GLFWwindow* window, double currentTime)
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(renderingProgram);
        glPointSize(30.0f);
        glDrawArrays(GL_POINTS, 0, 1);
        // glDrawArrays(GL_POINTS, 0, 36);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        double elapseTime = currentTime - this->currentTime;
        this->currentTime = currentTime;

        updateObjects(elapseTime);
        updateBuffers();

        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        // glEnableVertexAttribArray(0);


        // glUseProgram(renderingProgram);

        // // get the uniform variables for the MV and projection matrices
        // mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
        // projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

        // // build perspective matrix
        // glfwGetFramebufferSize(window, &width, &height);
        // aspect = (float)width / (float)height;
        // pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

        // // build view matrix, model matrix, and model-view matrix
        // vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        // mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
        // mvMat = vMat * mMat;

        // // copy perspective and MV matrices to corresponding uniform variables
        // glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        // associate VBO with the corresponding vertex attribute in the vertex shader
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        // adjust OpenGL settings and draw model
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawArrays(GL_TRIANGLES, 0, 36);
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

        glGenVertexArrays(numOfObjects, vao);
        glGenBuffers(numOfObjects, vbo);

        for (int i = 0; i < numOfObjects; ++i)
        {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

            std::vector<float>* vertices = objects[i].ModelVertices();
            (*objectVertices)[i] = vertices;
            glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(i);
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
