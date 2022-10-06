#include <pengine/model/model.h>

#include <iostream>

namespace pengine
{
    Model::Model()
    {
        //
    }

    std::vector<float> Model::Vertices()
    {
        return vertices;
    }

    void Model::SetVertices(std::vector<float> vertices)
    {
        this->vertices = vertices;
    }

    void Model::UpdateVertices(glm::vec3 offset)
    {
        for (int i=0; i<vertices.size(); i+=3)
        {
            vertices[i] += offset.x;
            vertices[i+1] += offset.y;
            vertices[i+2] += offset.z;
        }
    }


} // namespace pengine
