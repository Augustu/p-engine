#ifndef PENGINE_QTWORLD_H
#define PENGINE_QTWORLD_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

#include <pengine/force/gravity/point.h>
#include <pengine/world/object/object.h>
#include <pengine/model/manager.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

namespace pengine
{
    struct GLTexture {
        GLuint id;
        std::string type;
    };

    struct GLObject {
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        std::vector<GLuint> textureIDs;
        std::vector<GLTexture> glTextures;
        int indicesSize;
    };

    class QtWorld : public QWindow, protected QOpenGLExtraFunctions
    {
        Q_OBJECT
    public:
        explicit QtWorld(QWindow *parent = nullptr);
        ~QtWorld();

        void render(QPainter *painter);
        void render();
        void initialize();
        void setAnimating(bool animating);

        void PutObject(Object* object);
        void PutForce(GravityPoint force);

        pengine::Model* FetchModel(std::string name);

        void SetupObjects();
        void SetupShaders();

        std::string readShaderSource(const char *filePath);
        void LoadVertShader();
        void LoadFragShader();

    public slots:
        void renderLater();
        void renderNow();

    protected:
        bool event(QEvent *event) override;

        void exposeEvent(QExposeEvent *event) override;

        void display(double currentTime);

    private:
        bool m_animating = false;

        QOpenGLContext *m_context = nullptr;
        QOpenGLPaintDevice *m_device = nullptr;

        GLint m_posAttr = 0;
        GLint m_colAttr = 0;
        GLint m_matrixUniform = 0;

        QOpenGLShaderProgram *m_program = nullptr;
        GLuint renderingProgram;
        int m_frame = 0;

        std::vector<Object*> objects;
        std::vector<GLObject> glObjects;
        std::vector<GravityPoint> forces;

        std::vector<std::vector<float>*>* objectVertices;

        ModelManager modelManger;

        GLuint vertShader;
        GLuint fragShader;
    };
}

// namespace pengine
// {
//     struct GLTexture {
//         GLuint id;
//         std::string type;
//     };

//     struct GLObject {
//         GLuint vao;
//         GLuint vbo;
//         GLuint ebo;
//         std::vector<GLuint> textureIDs;
//         std::vector<GLTexture> glTextures;
//         int indicesSize;
//     };

//     class QtWorld
//     {
//     private:
//         int windowWidth;
//         int windowHeight;
//         std::string windowTitle;

//         GLFWwindow* window;

//         float focusX;
//         float focusY;
//         float focusZ;

//         GLuint renderingProgram;

//         std::vector<Object*> objects;

//         double currentTime;
//         std::vector<std::vector<float>*>* objectVertices;

//         std::vector<GLuint> vaos;
//         std::vector<int> indicesSizes;
//         std::vector<GLObject> glObjects;
//         std::vector<GravityPoint> forces;

//     public:
//         float cameraX;
//         float cameraY;
//         float cameraZ;


//     private:
//         void init(GLFWwindow* window);
//         void display(GLFWwindow* window, double currentTime);
//         void updateObjects(float elapseTime);
//         void updateBuffers();

//     public:
//         World(int windowWidth, int windowHeight, std::string windowTitle,
//                 float cameraX, float cameraY, float cameraZ);
//         ~World();

//         int Run();

//         // control
//         static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//         static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//         void SetFocus(float focusX, float focusY, float focusZ);

//         void PutObject(Object* object);
//         void PutForce(GravityPoint force);

//         void SetupObjects();
//         void SetupShaders();
//     };

// }

#endif