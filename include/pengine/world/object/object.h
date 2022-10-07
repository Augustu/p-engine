#ifndef PENGINE_WORLD_OBJECT_H
#define PENGINE_WORLD_OBJECT_H

#include <pengine/element/masspoint.h>
#include <pengine/model/model.h>

#include <string>

#include <GL/glew.h>

namespace pengine
{
    class Object : public MassPoint, public Model
    {
    private:
        std::string vertShaderPath;
        std::string fragShaderPath;

        GLuint vertShader;
        GLuint fragShader;

    public:
        Object();
        Object(std::string modelPath);
        virtual std::vector<float> Vertices();
        std::vector<float>* ModelVertices();
        void Update(float elapseTime);

        void SetVertShaderPath(std::string vertShaderPath);
        void SetFragShaderPath(std::string fragShaderPath);

        void LoadVertShader();
        void LoadFragShader();

        void LoadShaders(std::string vertShaderPath, std::string fragShaderPath);

        GLuint VertShader();
        GLuint FragShader();
    };
}

#endif