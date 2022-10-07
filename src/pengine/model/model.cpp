#include <pengine/model/model.h>

#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace pengine
{
    Model::Model()
    {
        //
    }

    void Model::SetModelPath(std::string modelPath)
    {
        this->modelPath = modelPath;
    }

    void Model::LoadModel()
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
        // Check for errors
        if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            exit(-1);
        }

        for (int i=0; i<scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];

            for (int j=0; j<scene->mMeshes[i]->mNumVertices; j++)
            {
                ai_real x = scene->mMeshes[i]->mVertices[j].x;
                ai_real y = scene->mMeshes[i]->mVertices[j].y;
                ai_real z = scene->mMeshes[i]->mVertices[j].z;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // std::cout << i+j+1 << " " << "x: " << x << " y: " << y << " z: " << z << std::endl;
            }

            for (int j=0; j<mesh->mNumFaces; j++)
            {
                aiFace face = mesh->mFaces[j];

                for (int k=0; k<face.mNumIndices; k++)
                {
                    indices.push_back(face.mIndices[k]);
                }
            }
        }

        // std::cout << indices.size() << std::endl;
    }


    std::vector<float> Model::Vertices()
    {
        return vertices;
    }

    void Model::SetVertices(std::vector<float> vertices)
    {
        this->vertices = vertices;
    }

    std::vector<int> Model::Indices()
    {
        return indices;
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
