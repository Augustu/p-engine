#include <pengine/world/object/object.h>

#include <pengine/glsl/glsl.h>

namespace pengine
{
    Object::Object()
    {
        //
    }

    Object::Object(std::string modelPath)
    {
        SetModelPath(modelPath);
        LoadModel();
    }

    std::vector<float> Object::Vertices()
    {
        return vertices;
    }

    std::vector<float>* Object::ModelVertices()
    {
        return &vertices;
    }

    void Object::Update(float elapseTime)
    {
        UpdatePosition(elapseTime);
        UpdateVertices(offset);
    }

    void Object::SetVertShaderPath(std::string vertShaderPath)
    {
        this->vertShaderPath = vertShaderPath;
    }

    void Object::SetFragShaderPath(std::string fragShaderPath)
    {
        this->fragShaderPath = fragShaderPath;
    }

    void Object::LoadVertShader()
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
    }

    void Object::LoadFragShader()
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
    }

    void Object::LoadShaders(std::string vertShaderPath, std::string fragShaderPath)
    {
        SetVertShaderPath(vertShaderPath);
        SetFragShaderPath(fragShaderPath);

        LoadVertShader();
        LoadFragShader();
    }

    GLuint Object::VertShader()
    {
        return vertShader;
    }

    GLuint Object::FragShader()
    {
        return fragShader;
    }

}
