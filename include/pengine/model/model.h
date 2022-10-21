#ifndef PENGINE_MODEL_H
#define PENGINE_MODEL_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace pengine
{
    #define MAX_BONE_INFLUENCE 4

    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
        unsigned char *data;
        int width;
        int height;
        int nrComponents;
    };

    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        std::vector<unsigned int> indices;
    };

    class Model
    {
    private:
        std::string modelPath;
        std::string directory;

        int numMesh = 0;

    protected:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        

    public:
        Model();
        void SetModelPath(std::string modelPath);
        void LoadModel();
        void processNode(aiNode *node, const aiScene *scene);
        void processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma, Texture *texture);
        std::vector<float> Vertices();
        void SetVertices(std::vector<float> vertices);
        void UpdateVertices(glm::vec3 position);
        std::vector<Mesh> GetMeshes();
    };
}

#endif