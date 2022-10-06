#ifndef PENGINE_PARTICLE_H
#define PENGINE_PARTICLE_H

#include <pengine/world/object/object.h>

#include <vector>
#include <string>

namespace pengine
{
    class Particle : public Object
    {
    public:
        Particle(float mass);
        std::vector<float> Vertices();
        void SetPosition(glm::vec3 position);
        void Update(float elapseTime);
    };
} // namespace pengine


#endif