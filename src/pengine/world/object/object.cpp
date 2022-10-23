#include <pengine/common.h>

#include <pengine/world/object/object.h>

#include <pengine/glsl/glsl.h>

namespace pengine
{
    Object::Object()
    {
    }

    Object::Object(std::string modelPath)
    {
        InitMassPoint();
    }

    void Object::SetModel(Model* model)
    {
        this->model = model;
    }

    std::vector<float> Object::Vertices()
    {
        return this->model->Vertices();
    }

    void Object::Update(float elapseTime)
    {
        UpdatePosition(elapseTime);
    }

    std::vector<Mesh> Object::GetMeshes()
    {
        return this->model->GetMeshes();
    }

    GLuint Object::VertShader()
    {
        return this->model->VertShader();
    }

    GLuint Object::FragShader()
    {
        return this->model->FragShader();
    }

    glm::mat4 Object::ModelMatrix()
    {
        // modelMatrix = glm::translate(modelMatrix, position);
        glm::vec3 position = this->GetPosition();
        // LOG(INFO) << "ModelMatrix position " << position.x << " " << position.y << " " << position.z;
        // LOG(INFO) << "offset " << offset.x << " " << offset.y << " " << offset.z;
        // return modelMatrix;
        return glm::translate(modelMatrix, position);
    }

}
