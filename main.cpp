#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
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
    //cam.position = Vector(10,0,0);
    cam.position.x = -10;
    cam.position.y = 0;
    cam.position.z = 0;
    
    //cam.rotation = Rotation(0,0,0);
    cam.rotation.x = 0;
    cam.rotation.y = 0;
    cam.rotation.z = 0;

    cam.focalLength = 10;

    cam.sensorSize.x = 200;
    cam.sensorSize.y = 200;

    //cam.resulotion = Vector(1920,1080);
    cam.resulotion.x = 1000;
    cam.resulotion.y = 1000;

    cam.skew = 1;


    List<Vector> vectorList;

    vectorList.Add(cam.CalculateScreenPoints(Vector(1,1,1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1,-1,1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1,1,-1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1,-1,-1)));

    vectorList.Add(cam.CalculateScreenPoints(Vector(-1,1,1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1,-1,1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1,1,-1)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1,-1,-1)));


    std::fstream file("out.svg");

    file<<"<svg height=\"1000\" width=\"1000\" xmlns=\"http://www.w3.org/2000/svg\">";

    for(int i = 0; i<vectorList.Size(); i++)
    {
        file<<"\t<circle r=\"45\" cx=\""<<vectorList[i].x<<"\" cy=\""<<vectorList[i].y<<"\" fill=\"red\" />";
    }

    file<<"</svg>";

    file.close();
}

int main()
{
    run();

    return 0;
}

