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
        return 1.0f;
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
        // force = glm::vec3(0.05f, 1.55f, 0.05f);
        // LOG(INFO) << "update force raw " << force.x << " " << force.y << " " << force.z;
        // LOG(INFO) << "update this->force before " << this->force.x << " " << this->force.y << " " << this->force.z;
        this->force += force;
        // LOG(INFO) << "update this->force after " << this->force.x << " " << this->force.y << " " << this->force.z;
    }

    void MassPoint::ClearForce()
    {
        this->force = glm::vec3(0.0f);
    }

    void MassPoint::UpdatePosition(float elapseTime)
    {
        // force = glm::vec3(0.5f, 1.55f, 0.05f);
        velocity += (force / mass) * elapseTime;
        // LOG(INFO) << "update mass " << mass;
        // LOG(INFO) << "update velocity " << velocity.x << " " << velocity.y << " " << velocity.z;
        // LOG(INFO) << "update force " << force.x << " " << force.y << " " << force.z;
        // LOG(INFO) << "update velocity " << velocity.x << " " << velocity.y << " " << velocity.z;

        // velocity = glm::vec3(1.0f);
        position += velocity * elapseTime;

        // LOG(INFO) << "update position " << position.x << " " << position.y << " " << position.z;
        // LOG(INFO) << "update this position " << this->position.x;
    }
}
