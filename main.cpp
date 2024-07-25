#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "logger.hpp"

#include <iostream>
#include <fstream>

void run()
{
    double sensor = 47;


    Camera cam;
    cam.position = Vector(3,1,5);
    cam.rotation = Rotation(0,0,0);
    cam.sensorSize = Vector(2*sensor,sensor);
    cam.resulotion = Vector(1400,700);
    cam.focalLength = 66;

    cam.PrintMatrix();

    List<Vector> vectorList;
    List<List<int>> faceList;

    std::fstream input("C:\\Users\\Baranyai Ferenc\\Desktop\\Sync-Engine\\sample\\Donuts.obj");

    char array[256];
    int n = 256;

    while(input.getline(array,n))
    {
        String line = array;

        if(line.Length() > 1 && line[0] == 'v' && line[1] == ' ')
        {
            List<String> list = line.Split(' ');

            char* x_char = list[1].toCharArray();
            char* y_char = list[2].toCharArray();
            char* z_char = list[3].toCharArray();

            vectorList.Add(cam.CalculateScreenPoints(Vector(atof(x_char),atof(y_char),atof(z_char))));

            delete[] x_char;
            delete[] y_char;
            delete[] z_char;
        }
        else if(line.Length() > 1 && line[0] == 'f' && line[1] == ' ')
        {
            List<String> list = line.Split(' ');
            List<int> faces;

            for(int i = 1; i<list.Size(); i++)
            {
                char* num = list[i].Split('/')[0].GetText();
                faces.Add(atoi(num));
                delete[] num;
            }

            faceList.Add(faces);
        }
    }

    input.close();

    double offset_x = 500;
    double offset_y = 300;

    std::fstream file("C:\\Users\\Baranyai Ferenc\\Desktop\\Sync-Engine\\sample\\out.svg", std::ios::out | std::ios::trunc);

    file<<"<svg height=\"900\" width=\"1600\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for(int x = 0; x<faceList.Size();x++)
    {
        file<<"\t<polygon points=\"";
        for(int y = 0; y<faceList[x].Size();y++)
        {
            file<<vectorList[faceList[x][y]-1].x+offset_x<<","<<vectorList[faceList[x][y]-1].y+offset_y<<" ";
        }

        file<<"\" style=\"stroke:"<<"black"<<";stroke-width:3\" fill-opacity=\"0.1\"/>\n";
    }

    double min = vectorList[0].z;
    double max = vectorList[0].z;

    for(int i = 0; i<vectorList.Size(); i++)
    {
        if(vectorList[i].z > max)
            max = vectorList[i].z;
        else if(vectorList[i].z < min)
            min = vectorList[i].z;
    }


    std::cout<<"Min: "<<min<<", max: "<<max<<std::endl;

    for(int i = 0; i<vectorList.Size(); i++)
    {
        if(false)
            file<<"\t<circle r=\"3\" cx=\""<<vectorList[i].x+offset_x<<"\" cy=\""<<vectorList[i].y+offset_y<<"\" fill=\"#D900FF\" />\n";
    }
    

    file<<"</svg>";

    file.close();

    Logger logger(std::cout, "main.cpp");

    logger.ConsoleLog("Done");
}

int main()
{
    run();

    return 0;
}

