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
    cam.position = Vector(7,2,5);
    cam.rotation = Rotation(0,0,0);
    cam.focalLength = 20;
    cam.sensorSize = Vector(36,18);
    cam.resulotion = Vector(1400,700);

    cam.skew = 0;


    List<Vector> vectorList;

    vectorList.Add(cam.CalculateScreenPoints(Vector(1.000000, 1.000000, -1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1.000000, -1.000000, -1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1.000000, 1.000000, 1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(1.000000, -1.000000, 1.000000)));

    vectorList.Add(cam.CalculateScreenPoints(Vector(-1.000000, 1.000000, -1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1.000000, -1.000000, -1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1.000000, 1.000000, 1.000000)));
    vectorList.Add(cam.CalculateScreenPoints(Vector(-1.000000, -1.000000, 1.000000)));


    std::fstream file("C:\\Users\\Baranyai Ferenc\\Desktop\\Sync-Engine\\out.svg", std::ios::out | std::ios::trunc);

    file<<"<svg height=\"700\" width=\"1400\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    int face[6][4] = {{1,5,7,3},{4,3,7,8},{8,7,5,6},{6,2,4,8},{2,1,3,4},{6,5,1,2}};

    for(int x = 0; x<6;x++)
    {
        file<<"\t<polygon points=\"";
        for(int y = 0; y<4;y++)
        {
            file<<vectorList[face[x][y]-1].x<<","<<vectorList[face[x][y]-1].y<<" ";
        }

        file<<"\" style=\"stroke:black;stroke-width:3\" fill-opacity=\"0.1\"/>\n";
    }

    for(int i = 0; i<vectorList.Size(); i++)
    {
        file<<"\t<circle r=\"3\" cx=\""<<vectorList[i].x<<"\" cy=\""<<vectorList[i].y<<"\" fill=\"red\" />\n";
    }
    

    file<<"</svg>";

    file.close();

    std::cout<<"Done!!!!!";
}

int main()
{
    run();

    return 0;
}

