#include <iostream>

#include <pengine/world/world.h>

#include <pengine/world/object/sphere.h>

using namespace std;
using namespace pengine;

int windowWidth = 720;
int windowHeight = 680;
string windowTitle = "Sphare demo";

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;

float mass = 1.0f;

int prec = 48;

// string modelPath = "../asserts/models/bob_lamp/bob_lamp.md5mesh";
// string modelPath = "../asserts/models/bob_lamp/bob_lamp.obj";
// string modelPath = "../asserts/models/cube/cube.obj";

string vertShaderPath = "../asserts/glsl/cube/vertShader.glsl";
string fragShaderPath = "../asserts/glsl/cube/fragShader.glsl";

int main()
{
    World world = World(windowWidth, windowHeight, windowTitle,
                        cameraX, cameraY, cameraZ);

    Sphere sphere = Sphere(prec);
    sphere.LoadShaders(vertShaderPath, fragShaderPath);

    world.PutObject(sphere);

    world.SetupObjects();
    world.SetupShaders();

    world.Run();

    return 0;
}
