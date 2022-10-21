#include <iostream>

#include <pengine/common.h>

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
float cameraZ = 100.0f;

float mass = 1.0f;

string modelPath = "../asserts/models/bob_lamp/bob_lamp.md5mesh";
// string modelPath = "../asserts/models/nanosuit/nanosuit.obj";
// string modelPath = "../asserts/models/bob_lamp/bob_lamp.obj";
// string modelPath = "../asserts/models/cube/cube.obj";

string vertShaderPath = "../asserts/glsl/bob_lamp/vertShader.glsl";
string fragShaderPath = "../asserts/glsl/bob_lamp/fragShader.glsl";

int main(int argc, char* argv[])
{
    InitLog(argv[0]);

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
