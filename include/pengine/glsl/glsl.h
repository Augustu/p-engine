#ifndef PENGINE_GLSL_H
#define PENGINE_GLSL_H

// #include <GL/glew.h>
#include <QOpenGLFunctions>

#include <string>
#include <vector>

#include <iostream>
#include <fstream>

std::string readShaderSource(const char *filePath);

GLuint createShaderProgram(const char *vertShaderPath, const char *fragShaderPath);

GLuint LoadTexture(const char *texImagePath);


// namespace pengine
// {
//     class Model
//     {
//     public:
//         const char* modelPath;
//         std::vector<float> vertexPositions;
//         std::vector<int> indicesPositions;

//     public:
//         Model(const char* modelPath);

//         bool Load();

//         const char* vertexPositionsData();
//         void vertexPositionsSize();
//         void vertexPositionsBufferSize();

//         void indicesPositionsData();
//         void indicesPositionsSize();
//         void indicesPositionsBufferSize();
//     };
// }


#endif