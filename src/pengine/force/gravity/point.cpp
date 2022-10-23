#include <pengine/force/gravity/point.h>

#include <pengine/common.h>

namespace pengine
{
    GravityPoint::GravityPoint(glm::vec3 center, float mass)
        : center(center), mass(mass)
    {
        //
    }

    void GravityPoint::SetConstG(float g)
    {
        constG = g;
    }


    void GravityPoint::UpdateForce(MassPoint* massPoint)
    {
        float massPointMass = massPoint->GetMass();
        glm::vec3 massPointPosition = massPoint->GetPosition();

        glm::vec3 force = center - massPointPosition;
        force = glm::normalize(force);

        float length = glm::length(center - massPointPosition);
        // LOG(INFO) << "length " << length;
        float strength = constG * mass * massPointMass / float(pow(length, 2));
        // LOG(INFO) << "constG " << constG;
        // LOG(INFO) << "mass " << mass;
        // LOG(INFO) << "massPointMass " << massPointMass;

        // LOG(INFO) << "ModelMatrix force " << force.x << " " << force.y << " " << force.z;

        force *= strength;

        massPoint->AddForce(force);
    }

}