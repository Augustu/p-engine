#ifndef PENGINE_GRAVITY_POINT_H
#define PENGINE_GRAVITY_POINT_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <pengine/element/masspoint.h>

namespace pengine
{
    class GravityPoint
    {
    private:
        glm::vec3 center;
        float mass;
        float constG = 1;

    public:
        GravityPoint(glm::vec3 center, float mass);
        void SetConstG(float g);
        void UpdateForce(MassPoint* massPoint);
    };
}

#endif