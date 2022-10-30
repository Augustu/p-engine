#include <iostream>

#include <pengine/common.h>

// #include <pengine/model/manager.h>

#include <QGuiApplication>
#include <QtDebug>

#include <pengine/world/qtworld.h>

using namespace std;
using namespace pengine;

int windowWidth = 1024;
int windowHeight = 1024;
string windowTitle = "Particle demo";

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 40.0f;

float mass = 1.0f;

int main(int argc, char* argv[])
{
    InitLog(argv[0]);

    QGuiApplication app(argc, argv);

    QtWorld world;

    GravityPoint gravityPoint(glm::vec3(0.0f),  1.0f);
    gravityPoint.SetConstG(10e3);

    world.PutForce(gravityPoint);

    world.resize(640, 480);
    world.show();

    world.setAnimating(true);

    return app.exec();
}
