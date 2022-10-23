#ifndef PENGINE_WORLD_OBJECT_H
#define PENGINE_WORLD_OBJECT_H

#include <pengine/element/masspoint.h>
#include <pengine/model/model.h>

#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pengine
{
    class Object : public MassPoint
    {
    private:
        Model* model;

        glm::mat4 modelMatrix = glm::mat4(1.0f);

    public:
        Object();
        Object(std::string modelPath);
        void SetModel(Model* model);
        virtual std::vector<float> Vertices();
        void Update(float elapseTime);

        std::vector<Mesh> GetMeshes();

        void LoadShaders(std::string vertShaderPath, std::string fragShaderPath);

        GLuint VertShader();
        GLuint FragShader();

        glm::mat4 ModelMatrix();
    };
}

#endif