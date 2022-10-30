#include <pengine/common.h>

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

    void MassPoint::InitMassPoint()
    {
        this->position = glm::vec3(1.0f);
    }

    void MassPoint::SetMass(float mass)
    {
        this->mass = mass;
    }

    float MassPoint::GetMass()
    {
        return this->mass;
    }

    void MassPoint::SetPosition(glm::vec3 position)
    {
        this->position = position;
    }

    glm::vec3 MassPoint::GetPosition()
    {
        return this->position;
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

    void MassPoint::SetForce(glm::vec3 force)
    {
        // this->force = force;
    }

    void MassPoint::AddForce(glm::vec3 force)
    {
        this->force += force;
    }

    void MassPoint::ClearForce()
    {
        this->force = glm::vec3(0.0f);
    }

    void MassPoint::UpdatePosition(float elapseTime)
    {
        velocity += (force / mass) * elapseTime;
        position += velocity * elapseTime;
    }
}
