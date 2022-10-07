#ifndef PENGINE_MODEL_H
#define PENGINE_MODEL_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace pengine
{
    class Model
    {
    private:
        std::string modelPath;

    protected:
        std::vector<float> vertices;
        std::vector<int> indices;

    public:
        Model();
        void SetModelPath(std::string modelPath);
        void LoadModel();
        std::vector<float> Vertices();
        std::vector<int> Indices();
        void SetVertices(std::vector<float> vertices);
        void UpdateVertices(glm::vec3 position);
    };
}

#endif