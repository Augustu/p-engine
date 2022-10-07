#include <pengine/world/object/Sphere.h>

namespace pengine
{
    Sphere::Sphere(int prec) {   // prec是精度，也就是切片的数量
        init(prec);

        std::vector<int> ind = getIndices();

        int numIndices = getNumIndices();
        for (int i = 0; i < numIndices; i++) {
            vertices.push_back((Vec3Vertices[ind[i]]).x);
            vertices.push_back((Vec3Vertices[ind[i]]).y);
            vertices.push_back((Vec3Vertices[ind[i]]).z);

            tvalues.push_back((texCoords[ind[i]]).s);
            tvalues.push_back((texCoords[ind[i]]).t);

            nvalues.push_back((normals[ind[i]]).x);
            nvalues.push_back((normals[ind[i]]).y);
            nvalues.push_back((normals[ind[i]]).z);
        }

    }

    float Sphere::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

    std::vector<float> Sphere::Vertices()
    {
        return vertices;
    }

    std::vector<float> Sphere::TexCoords()
    {
        return tvalues;
    }

    std::vector<float> Sphere::Normals()
    {
        return nvalues;
    }

    void Sphere::Update(float elapseTime)
    {
        //
    }

    void Sphere::init(int prec) {
        numVertices = (prec + 1) * (prec + 1);
        numIndices = prec * prec * 6;
        // std::vector::push_back() 在向量的末尾增加一个新元素，并为向量长度加 1
        for (int i = 0; i < numVertices; i++) { Vec3Vertices.push_back(glm::vec3()); }
        for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
        for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
        for (int i = 0; i < numIndices; i++) { indices.push_back(0); }

        // 计算三角形顶点
        for (int i = 0; i <= prec; i++) {
            for (int j = 0; j <= prec; j++) {
                float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
                float x = -(float)cos(toRadians(j*360.0f / prec)) * (float)abs(cos(asin(y)));
                float z = (float)sin(toRadians(j*360.0f / prec)) * (float)abs(cos(asin(y)));
                Vec3Vertices[i*(prec + 1) + j] = glm::vec3(x, y, z);
                texCoords[i*(prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
                normals[i*(prec + 1) + j] = glm::vec3(x,y,z);
            }
        }

        // 计算三角形索引
        for (int i = 0; i<prec; i++) {
            for (int j = 0; j<prec; j++) {
                indices[6 * (i*prec + j) + 0] = i*(prec + 1) + j;
                indices[6 * (i*prec + j) + 1] = i*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 2] = (i + 1)*(prec + 1) + j;
                indices[6 * (i*prec + j) + 3] = i*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 4] = (i + 1)*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 5] = (i + 1)*(prec + 1) + j;
            }
        }
    }

    // 读取函数
    int Sphere::getNumVertices() { return numVertices; }
    int Sphere::getNumIndices() { return numIndices; }
    std::vector<int> Sphere::getIndices() { return indices; }
    std::vector<glm::vec3> Sphere::getVertices() { return Vec3Vertices; }
    std::vector<glm::vec2> Sphere::getTexCoords() { return texCoords; }
    std::vector<glm::vec3> Sphere::getNormals() { return normals; }

}
