#include <iostream>

#include <pengine/world/world.h>

#include <pengine/model/cube.h>

#include <pengine/world/object/object.h>

using namespace std;
using namespace pengine;

int windowWidth = 720;
int windowHeight = 680;
string windowTitle = "Model demo";

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 4.0f;

float mass = 1.0f;

// string modelPath = "../asserts/models/bob_lamp/bob_lamp.md5mesh";
string modelPath = "../asserts/models/cube/cube.obj";

string vertShaderPath = "../asserts/glsl/cube/vertShader.glsl";
string fragShaderPath = "../asserts/glsl/cube/fragShader.glsl";

int main()
{
    World world = World(windowWidth, windowHeight, windowTitle,
                        cameraX, cameraY, cameraZ);

    Object object = Object(modelPath);
    object.LoadShaders(vertShaderPath, fragShaderPath);

    world.PutObject(object);

    world.SetupObjects();
    world.SetupShaders();

    world.Run();

    return 0;
}
