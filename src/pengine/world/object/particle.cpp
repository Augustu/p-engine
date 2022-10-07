#include <pengine/world/object/particle.h>

#include <pengine/glsl/glsl.h>

namespace pengine
{
    Particle::Particle(float mass)
    {
        // SetMass(mass);
        SetVertShaderPath("../asserts/glsl/particle/vertShader.glsl");
        SetFragShaderPath("../asserts/glsl/particle/fragShader.glsl");

        LoadVertShader();
        LoadFragShader();
    }

    void Particle::SetPosition(glm::vec3 position)
    {
        this->position = position;

        vertices.push_back(position.x);
        vertices.push_back(position.y);
        vertices.push_back(position.z);
    }

    std::vector<float> Particle::Vertices()
    {
        return vertices;
    }

    void Particle::Update(float elapseTime)
    {
        Update(elapseTime);
        SetPosition(position);
        std::cout << "position" << std::endl;
    }
}
