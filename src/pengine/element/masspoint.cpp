#include <pengine/element/masspoint.h>

#include <iostream>

namespace pengine
{
    MassPoint::MassPoint()
    {
        //
    }

    MassPoint::MassPoint(float mass)
        : mass(mass)
    {
        //
    }

    void SetMass(float mass)
    {
        mass = mass;
    }

    void MassPoint::SetPosition(glm::vec3 position)
    {
        this->position = position;
    }

    glm::vec3 MassPoint::GetPosition()
    {
        return position;
    }

    void MassPoint::SetVelocity(glm::vec3 velocity)
    {
        this->velocity = velocity;
    }

    void MassPoint::AddVelocity(glm::vec3 velocity)
    {
        this->velocity += velocity;
    }

    void MassPoint::SetAcceleration(glm::vec3 acceleration)
    {
        this->acceleration = acceleration;
    }

    void MassPoint::AddAcceleration(glm::vec3 acceleration)
    {
        acceleration = acceleration;
    }

    void MassPoint::UpdatePosition(float elapseTime)
    {
        offset = velocity * elapseTime;

        position = position + offset;
        velocity = velocity + acceleration * elapseTime;
    }
}
