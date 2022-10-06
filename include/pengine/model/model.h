#ifndef PENGINE_MODEL_H
#define PENGINE_MODEL_H

#include <vector>

#include <glm/glm.hpp>

namespace pengine
{
    class Model
    {
    private:

    public:
        std::vector<float> vertices;

    public:
        Model();
        std::vector<float> Vertices();
        void SetVertices(std::vector<float> vertices);
        void UpdateVertices(glm::vec3 position);
    };
}

#endif