#include <iostream>

#include <pengine/world/world.h>

#include <pengine/model/cube.h>

#include <pengine/world/object/particle.h>

using namespace std;
using namespace pengine;

int windowWidth = 720;
int windowHeight = 680;
string windowTitle = "Particle demo";

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 4.0f;

float mass = 1.0f;

int main()
{
    World world = World(windowWidth, windowHeight, windowTitle,
                        cameraX, cameraY, cameraZ);

    Particle particle = Particle(mass);
    particle.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    particle.SetVelocity(glm::vec3(0.0f, 2.5f, 0.0f));
    particle.SetAcceleration(glm::vec3(0.0f, -1.75f, 0.0f));

    world.PutObject(particle);

    world.SetupObjects();
    world.SetupShaders();

    world.Run();

    return 0;
}
