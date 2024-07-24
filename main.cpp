#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
#include "vector.hpp"
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
    cam.position = Vector(-10,0,0);
    cam.rotation = Rotation(0,0,0);
    cam.focalLength = 10;
    cam.sensorSize = Vector(20,20);
    cam.resulotion = Vector(100,100);

    cam.skew = 2;


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

    file<<"<svg height=\"100\" width=\"100\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for(int i = 0; i<vectorList.Size(); i++)
    {
        file<<"\t<circle r=\"2\" cx=\""<<vectorList[i].x*-1<<"\" cy=\""<<vectorList[i].y*-1<<"\" fill=\"red\" />\n";
    }

    file<<"</svg>";

    file.close();
}

int main()
{
    run();

    return 0;
}

