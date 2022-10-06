#include <pengine/glsl/glsl.h>

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SOIL2.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace std;


string readShaderSource(const char *filePath)
{
    string content;
    ifstream fileSteam(filePath, ios::in);

    string line = "";

    while (!fileSteam.eof())
    {
        getline(fileSteam, line);
        content.append(line + "\n");
    }

    fileSteam.close();
    return content;
}

GLuint createShaderProgram(const char *vertShaderPath, const char *fragShaderPath)
{
    string vertShaderStr = readShaderSource(vertShaderPath);
    string fragShaderStr = readShaderSource(fragShaderPath);

    const char *vshaderSource = vertShaderStr.c_str();
    const char *fshaderSource = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    GLint success;
    GLchar infoLog[512];

    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }

    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}