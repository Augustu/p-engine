#include <pengine/world/qtworld.h>

#include <assert.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QScreen>

#include <pengine/common.h>

using namespace std;

string modelName = "sphere";
string modelPath = "../asserts/models/sphere/sphere.obj";

string vertShaderPath = "../asserts/glsl/sphere-with-speed/vertShader.glsl";
string fragShaderPath = "../asserts/glsl/sphere-with-speed/fragShader.glsl";

namespace pengine
{
    QtWorld::QtWorld(QWindow *parent)
    : QWindow(parent)
    {
        setSurfaceType(QWindow::OpenGLSurface);
    }

    QtWorld::~QtWorld()
    {
        delete m_device;
    }

    void QtWorld::render(QPainter *painter)
    {
        Q_UNUSED(painter);

        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        m_program->bind();

        QMatrix4x4 projMatrix;
        projMatrix.perspective(120.0f, width() / height(), 0.1f, 100.0f);

        glm::mat4 vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));

        for (unsigned int i=0; i<glObjects.size(); ++i)
        {
            GLObject glObject = glObjects[i];

            Object* object = objects[i];

            // update force
            for (GravityPoint force : forces)
            {
                force.UpdateForce(object);
            }

            // object->UpdatePosition(elapseTime);
            object->UpdatePosition(0.01f);

            glm::mat4 model = object->ModelMatrix();

            GLuint mvLoc = m_program->uniformLocation("mv_matrix");
            Q_ASSERT(mvLoc != -1);
            GLuint projLoc = m_program->uniformLocation("proj_matrix");
            Q_ASSERT(projLoc != -1);

            m_program->setUniformValue(mvLoc, QMatrix4x4(glm::value_ptr(vMat * model)).transposed());
            m_program->setUniformValue(projLoc, projMatrix);

            unsigned int diffuseNr  = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr   = 1;
            unsigned int heightNr   = 1;

            for(unsigned int j = 0; j < glObject.glTextures.size(); j++)
            {
                glActiveTexture(GL_TEXTURE0 + j); // active proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                std::string number;
                std::string name = glObject.glTextures[j].type;
                if(name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if(name == "texture_specular")
                    number = std::to_string(specularNr++); // transfer unsigned int to string
                else if(name == "texture_normal")
                    number = std::to_string(normalNr++); // transfer unsigned int to string
                else if(name == "texture_height")
                    number = std::to_string(heightNr++); // transfer unsigned int to string

                // now set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(renderingProgram, (name + number).c_str()), j);
                // and finally bind the texture
                glBindTexture(GL_TEXTURE_2D, glObject.glTextures[j].id);
            }

            glBindVertexArray(glObject.vao);
            glDrawElements(GL_TRIANGLES, glObject.indicesSize, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            object->ClearForce();
        }

        ++m_frame;
    }

    void QtWorld::render()
    {
        if (!m_device)
        {
            m_device = new QOpenGLPaintDevice;
            renderingProgram = glCreateProgram();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        m_device->setSize(size() * devicePixelRatio());
        m_device->setDevicePixelRatio(devicePixelRatio());

        QPainter painter(m_device);
        render(&painter);
    }

    void QtWorld::renderLater()
    {
        requestUpdate();
    }

    bool QtWorld::event(QEvent *event)
    {
        switch (event->type()) {
        case QEvent::UpdateRequest:
            renderNow();
            return true;
        default:
            return QWindow::event(event);
        }
    }

    void QtWorld::exposeEvent(QExposeEvent *event)
    {
        Q_UNUSED(event);

        if (isExposed())
            renderNow();
    }

    void QtWorld::renderNow()
    {
        if (!isExposed())
            return;

        bool needsInitialize = false;

        if (!m_context) {
            m_context = new QOpenGLContext(this);
            m_context->setFormat(requestedFormat());
            m_context->create();

            needsInitialize = true;
        }

        m_context->makeCurrent(this);

        if (needsInitialize) {
            initializeOpenGLFunctions();
            initialize();

            modelManger = ModelManager();

            ModelDefine sphere = ModelDefine{
                Name: modelName,
                ModelPath: modelPath,
                VertShaderPath: vertShaderPath,
                FragShaderPath: fragShaderPath,
            };

            modelManger.RegisterModel(&sphere);
            modelManger.LoadModels();

            pengine::Model* sphereModel = FetchModel(modelName);

            int total = 2000;

            for (int i=0; i<total; ++i)
            {
                Object* object = new Object();
                object->SetModel(sphereModel);

                float y = -((rand()+1) % 50 + 1);
                float vx = (rand() + 1) % 10 + 1;

                object->SetPosition(glm::vec3(0.0f, y, 0.0f));
                object->SetVelocity(glm::vec3(vx, 0.0f, 0.0f));
                object->SetAcceleration(glm::vec3(0.0f));
                object->SetMass(1.0f);

                PutObject(object);
            }

            SetupObjects();
            SetupShaders();
        }

        render();

        m_context->swapBuffers(this);

        if (m_animating)
            renderLater();
    }

    void QtWorld::setAnimating(bool animating)
    {
        m_animating = animating;

        if (animating)
            renderLater();
    }

    void QtWorld::initialize()
    {
        m_program = new QOpenGLShaderProgram(this);
    }

    void QtWorld::PutObject(Object* object)
    {
        objects.push_back(object);
    }

    void QtWorld::PutForce(GravityPoint force)
    {
        forces.push_back(force);
    }

    pengine::Model* QtWorld::FetchModel(std::string name)
    {
        return modelManger.FetchModel(name);
    }

    void QtWorld::SetupObjects()
    {
        int numOfObjects = objects.size();

        objectVertices = new std::vector<std::vector<float>*>(numOfObjects, NULL);

        for (int i = 0; i < numOfObjects; ++i)
        {
            Object* object = objects[i];

            std::vector<Mesh> meshes = object->GetMeshes();

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

    void QtWorld::SetupShaders()
    {
        Object* object = objects.at(0);

        GLuint vShader = object->VertShader();
        GLuint fShader = object->FragShader();

        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(vertShaderPath));
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(fragShaderPath));

        m_program->bind();
    }

    void QtWorld::LoadVertShader()
    {
        std::string vertShaderStr = readShaderSource(vertShaderPath.c_str());

        const char *vshaderSource = vertShaderStr.c_str();

        vertShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertShader, 1, &vshaderSource, NULL);

        GLint success;
        GLchar infoLog[512];

        glCompileShader(vertShader);
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            exit(-1);
        }

        LOG(INFO) << "LoadVertShader done";
    }

    void QtWorld::LoadFragShader()
    {
        std::string fragShaderStr = readShaderSource(fragShaderPath.c_str());

        const char *fshaderSource = fragShaderStr.c_str();

        fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragShader, 1, &fshaderSource, NULL);

        GLint success;
        GLchar infoLog[512];

        glCompileShader(fragShader);
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            exit(-1);
        }

        LOG(INFO) << "LoadFragShader done";
    }

    std::string QtWorld::readShaderSource(const char *filePath)
    {
        std::string content;
        std::ifstream fileSteam(filePath, std::ios::in);

        std::string line = "";

        while (!fileSteam.eof())
        {
            std::getline(fileSteam, line);
            content.append(line + "\n");
        }

        fileSteam.close();
        return content;
    }

}
