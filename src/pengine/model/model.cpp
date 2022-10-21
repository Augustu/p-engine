#include <pengine/model/model.h>

#include <iostream>

#include <stb/stb_image.h>

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

        directory = modelPath.substr(0, modelPath.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (int i=0; i<node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh, scene);
        }

        for (int i=0; i<node->mNumChildren; ++i)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    void Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        Mesh singleMesh;
        std::vector<Vertex> meshVertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (int i=0; i<mesh->mNumVertices; ++i)
        {
            Vertex vertex;

            aiVector3D meshVertex = mesh->mVertices[i];
            vertex.Position = glm::vec3(meshVertex.x, meshVertex.y, meshVertex.z);

            if (mesh->HasNormals())
            {
                aiVector3D meshNormal = mesh->mNormals[i];
                vertex.Normal = glm::vec3(meshNormal.x, meshNormal.y, meshNormal.z);
            }

            aiVector3D* meshTextureCoord = mesh->mTextureCoords[0];
            if (meshTextureCoord)
            {
                vertex.TexCoords = glm::vec2(meshTextureCoord[i].x, meshTextureCoord[i].y);
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            if (mesh->HasTangentsAndBitangents())
            {
                aiVector3D meshTangent = mesh->mTangents[i];
                vertex.Tangent = glm::vec3(meshTangent.x, meshTangent.y, meshTangent.z);

                aiVector3D meshBitangent = mesh->mBitangents[i];
                vertex.Bitangent = glm::vec3(meshBitangent.x, meshBitangent.y, meshBitangent.z);
            }

            meshVertices.push_back(vertex);
        }

        singleMesh.vertices = meshVertices;

        for (int i=0; i<mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        singleMesh.indices = indices;

        // add materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        singleMesh.textures = textures;

        meshes.push_back(singleMesh);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if(!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory, false, &texture);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }

    unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma, Texture *texture)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            texture->width = width;
            texture->height = height;
            texture->nrComponents = nrComponents;
            texture->data = data;
        }

        return 0;
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

    std::vector<Mesh> Model::GetMeshes()
    {
        return meshes;
    }

} // namespace pengine
