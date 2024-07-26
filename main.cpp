#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "basiccamera.hpp"
#include "logger.hpp"
#include "object.hpp"
#include "import.hpp"

#include "svgcreator.hpp"

#include <iostream>
#include <fstream>

void run()
{
    double sensor = 47;

/*
    Camera cam;
    cam.position = Vector(3,1,5);
    cam.rotation = Rotation(0,0,0);
    cam.sensorSize = Vector(2*sensor,sensor);
    cam.resulotion = Vector(1400,700);
    cam.focalLength = 66;

    cam.PrintMatrix();*/

    BasicCamera cam;
    cam.far = 5000;
    cam.near = 0.1;
    cam.fov = 50;
    cam.position = Vector(-4000,1000,3000);
    cam.resulotion = Vector(1600,900);
    cam.rotation = Rotation(0,60,0);

    std::cout<<cam.GetScreenPoint(Vector(5,1,10));

    Object obj = Import::ImportObj("sample/Cube.obj");

    SvgCreator svg("outdraw.svg");
    svg.DrawSVG(obj, cam);
    
    Logger logger(std::cout, "main.cpp");

    logger.ConsoleLog("Done");
}

#include "stopper.hpp"

int main()
{
    Stopper stopper;
    stopper.Set();

    run();

    std::cout<<"Time to render: "<<stopper.Stop();

    return 0;
}

