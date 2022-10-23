#include <iostream>

#include <pengine/common.h>

#include <pengine/world/world.h>

#include <pengine/model/manager.h>

#include <pengine/world/object/particle.h>

using namespace std;
using namespace pengine;

int windowWidth = 1024;
int windowHeight = 1024;
string windowTitle = "Particle demo";

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 40.0f;

float mass = 1.0f;

string modelName = "sphere";
string modelPath = "../asserts/models/sphere/sphere.obj";

string vertShaderPath = "../asserts/glsl/sphere-with-speed/vertShader.glsl";
string fragShaderPath = "../asserts/glsl/sphere-with-speed/fragShader.glsl";

int main(int argc, char* argv[])
{
    InitLog(argv[0]);

    World world = World(windowWidth, windowHeight, windowTitle,
                        cameraX, cameraY, cameraZ);

    GravityPoint gravityPoint(glm::vec3(0.0f),  1.0f);
    gravityPoint.SetConstG(10e3);

    world.PutForce(gravityPoint);

    ModelManager modelManger = ModelManager();

    ModelDefine sphere = ModelDefine{
        Name: modelName,
        ModelPath: modelPath,
        VertShaderPath: vertShaderPath,
        FragShaderPath: fragShaderPath,
    };

    modelManger.RegisterModel(&sphere);
    modelManger.LoadModels();

    pengine::Model* sphereModel = modelManger.FetchModel(sphere.Name);

    int total = 1000;

    std::vector<Object> objects[total];

    for (int i=0; i<total; ++i)
    {
        Object* object = new Object();
        object->SetModel(sphereModel);

        float y = -((rand()+1) % 50 + 1);
        float vx = (rand() + 1) % 10 + 1;

        object->SetPosition(glm::vec3(0.0f, y, 0.0f));
        object->SetVelocity(glm::vec3(vx, 0.0f, 0.0f));
        object->SetAcceleration(glm::vec3(0.0f));
        object->SetMass(1.0f);

        world.PutObject(object);
    }

    world.SetupObjects();
    world.SetupShaders();

    world.Run();

    return 0;
}
