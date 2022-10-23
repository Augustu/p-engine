#ifndef PENGINE_ELEMENT_MASSPOINT_H
#define PENGINE_ELEMENT_MASSPOINT_H

#include <glm/glm.hpp>

namespace pengine
{
    class MassPoint
    {
    private:

    protected:
        float mass;

        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;
        glm::vec3 force = glm::vec3(0.0f);

        glm::vec3 offset;

    public:
        MassPoint();
        MassPoint(float mass);

        void InitMassPoint();

        void SetMass(float mass);
        float GetMass();

        void SetPosition(glm::vec3 position);
        glm::vec3 GetPosition();

        void SetVelocity(glm::vec3 velocity);
        void AddVelocity(glm::vec3 velocity);

        void SetAcceleration(glm::vec3 acceleration);
        void AddAcceleration(glm::vec3 acceleration);

        void SetForce(glm::vec3 force);
        void AddForce(glm::vec3 force);
        void ClearForce();

        void UpdatePosition(float elapseTime);
    };
}

#endif