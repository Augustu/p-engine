#ifndef PENGINE_WORLD_SPHERE_H
#define PENGINE_WORLD_SPHERE_H

#include <pengine/world/object/object.h>

namespace pengine
{
    class Sphere : public Object
    {
    private:
        int numVertices;
        int numIndices;
        std::vector<glm::vec3> Vec3Vertices;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;

        std::vector<float> pvalues;     // 顶点位置
        std::vector<float> tvalues;     // 纹理坐标
        std::vector<float> nvalues;     // 法向量

    private:
        void init(int);
        float toRadians(float degrees);

    public:
        Sphere(int prec);
        std::vector<float> Vertices();
        std::vector<float> TexCoords();
        std::vector<float> Normals();
        void Update(float elapseTime);
        int getNumVertices();
        int getNumIndices();
        std::vector<int> getIndices();
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec2> getTexCoords();
        std::vector<glm::vec3> getNormals();
    };
}

#endif