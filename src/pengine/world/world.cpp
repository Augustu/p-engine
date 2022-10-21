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

        glEnable(GL_DEPTH_TEST);

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);
        glfwSetScrollCallback(window, scroll_callback);

        glfwSwapInterval(1);
        init(window);
    }

    World::~World()
    {
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

        // glm::mat4 pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

        // // build view matrix, model matrix, and model-view matrix
        // glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(focusX, focusY, focusZ));

        int total = 3;

        for (int i=0; i<total; ++i)
        {

            glm::mat4 pMat = glm::perspective(2*1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
            // glm::mat4 pMat = glm::perspective(2*1.0472f, aspect, -0.1f, -1000.0f); // 1.0472 radians = 60 degrees
            // glm::mat4 pMat = glm::perspective(0.0f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

            // // build view matrix, model matrix, and model-view matrix
            glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
            // glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1000.0f));
            // glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1000.0f));
            // // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(focusX, focusY, focusZ));

            // glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(i*8.0f, 0.0f, 0.0f));
            // glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f*i, glm::vec3(0.0f, 1.0f, 0.0f));

            // glm::mat4 mMat = glm::mat4(1.0f);
            // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f));
            // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(currentTime*50.0f, 0.0f, 0.0f));
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

            model = glm::translate(model, glm::vec3(i*50.0f, 0.0f, 0.0f));
            model = glm::rotate(model, -glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, 1.75f*float(currentTime), glm::vec3(0.0f, 0.0f, 1.0f));

            // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(i*50.0f, 0.0f, 0.0f));
            // glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f*float(currentTime), glm::vec3(0.0f, 1.0f, 0.0f));
            // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3((i+1)*50.0f, 0.0f, 0.0f));
            // glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(i+1), glm::vec3(0.0f, 1.0f, 0.0f));
            // glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(i*50.0f, 0.0f, 0.0f));
            // glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f*i, glm::vec3(0.0f, 1.0f, 0.0f));

            // mMat = rMat * mMat;
            // mMat = mMat * rMat;
            // glm::mat4 mMat = rMat * tMat;
            // glm::mat4 mMat = rMat * tMat;
            // glm::mat4 mMat = tMat * rMat;
            glm::mat4 mvMat = vMat * model;
            // glm::mat4 mvMat = vMat * mMat;
            // glm::mat4 mvMat = vMat * rMat;
            // glm::mat4 mvMat = vMat;

            // copy perspective and MV matrices to corresponding uniform variables
            glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));


            for (unsigned int j=0; j<glObjects.size(); ++j)
            {
                GLObject glObject = glObjects[j];

                unsigned int diffuseNr  = 1;
                unsigned int specularNr = 1;
                unsigned int normalNr   = 1;
                unsigned int heightNr   = 1;

                for(unsigned int i = 0; i < glObject.glTextures.size(); i++)
                {
                    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = glObject.glTextures[i].type;
                    if(name == "texture_diffuse")
                        number = std::to_string(diffuseNr++);
                    else if(name == "texture_specular")
                        number = std::to_string(specularNr++); // transfer unsigned int to string
                    else if(name == "texture_normal")
                        number = std::to_string(normalNr++); // transfer unsigned int to string
                    else if(name == "texture_height")
                        number = std::to_string(heightNr++); // transfer unsigned int to string

                    // now set the sampler to the correct texture unit
                    glUniform1i(glGetUniformLocation(renderingProgram, (name + number).c_str()), i);
                    // and finally bind the texture
                    glBindTexture(GL_TEXTURE_2D, glObject.glTextures[i].id);
                }

                glBindVertexArray(glObject.vao);
                glDrawElements(GL_TRIANGLES, glObject.indicesSize, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }

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

        for (int i = 0; i < numOfObjects; ++i)
        {
            Object object = objects[i];

            std::vector<Mesh> meshes = object.GetMeshes();

            for (int m=0; m<meshes.size(); ++m)
            {
                Mesh mesh = meshes[m];

                std::vector<Vertex> vertices = mesh.vertices;
                std::vector<unsigned int> indices = mesh.indices;

                GLObject glObject;

                GLuint vao;
                GLuint vbo;
                GLuint ebo;

                int numMeshes = 1;

                glGenVertexArrays(numMeshes, &vao);
                glGenBuffers(numMeshes, &vbo);
                glGenBuffers(numMeshes, &ebo);

                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);

                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

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

                std::vector<Texture> textures = mesh.textures;

                unsigned int diffuseNr  = 1;
                unsigned int specularNr = 1;
                unsigned int normalNr   = 1;
                unsigned int heightNr   = 1;

                for (unsigned int i = 0; i < textures.size(); ++i)
                {
                    Texture texture = textures.at(i);
                    int nrComponents = texture.nrComponents;

                    GLenum format;
                    if (nrComponents == 1)
                        format = GL_RED;
                    else if (nrComponents == 3)
                        format = GL_RGB;
                    else if (nrComponents == 4)
                        format = GL_RGBA;

                    unsigned int textureID;
                    glGenTextures(1, &textureID);
                    int width = texture.width;
                    int height = texture.height;
                    unsigned char *data = texture.data;

                    glBindTexture(GL_TEXTURE_2D, textureID);
                    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = texture.type;
                    if(name == "texture_diffuse")
                        number = std::to_string(diffuseNr++);
                    else if(name == "texture_specular")
                        number = std::to_string(specularNr++); // transfer unsigned int to string
                    else if(name == "texture_normal")
                        number = std::to_string(normalNr++); // transfer unsigned int to string
                    else if(name == "texture_height")
                        number = std::to_string(heightNr++); // transfer unsigned int to string

                    // now set the sampler to the correct texture unit
                    glUniform1i(glGetUniformLocation(renderingProgram, (name + number).c_str()), i);
                    // and finally bind the texture
                    glBindTexture(GL_TEXTURE_2D, textureID);

                    GLTexture glTexture;
                    glTexture.id = textureID;
                    glTexture.type = texture.type;

                    glObject.glTextures.push_back(glTexture);
                }

                glObject.vao = vao;
                glObject.vbo = vbo;
                glObject.ebo = ebo;
                glObject.indicesSize = indices.size();

                glObjects.push_back(glObject);
            }

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
