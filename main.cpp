#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
#include "logger.hpp"
#include "vector.h"
#include "camera.hpp"

#include <iostream>
#include <fstream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    Camera cam;
    cam.position = Vector(10,0,0);
    cam.rotation = Rotation(0,0,0);
    cam.focalLength = 50;
    cam.sensorSize = 10;
    cam.resulotion = Vector(1920,1080);
    cam.skew = 1;

    cam.PrintMatrix();
}

int main()
{
    run();

    return 0;
}

