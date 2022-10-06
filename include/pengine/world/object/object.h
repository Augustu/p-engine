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
        virtual std::vector<float> Vertices();
        std::vector<float>* ModelVertices();
        void Update(float elapseTime);

        void SetVertShaderPath(std::string vertShaderPath);
        void SetFragShaderPath(std::string fragShaderPath);

        void LoadVertShader();
        void LoadFragShader();

        GLuint VertShader();
        GLuint FragShader();
    };
}

#endif