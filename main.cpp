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

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void run()
{
    double sensor = 1;


    Camera cam;
    cam.position = Vector(1000000,0,0);
    cam.rotation = Rotation(0,0,0);
    cam.sensorSize = Vector(2*sensor,sensor);
    cam.resulotion = Vector(1400,700);
    cam.focalLength = 1;

    List<Vector> vectorList;
    List<List<int>> faceList;

    std::fstream input("sample/Apple.obj");

    char array[256];
    int n = 256;

    while(input.getline(array,n))
    {
        String line = array;

        if(line.Length() > 1 && line[0] == 'v' && line[1] == ' ')
        {
            List<String> list = line.Split(' ');

            char* x_char = list[2].toCharArray();
            char* y_char = list[3].toCharArray();
            char* z_char = list[4].toCharArray();

            vectorList.Add(Vector(atof(x_char)+2400,atof(y_char)+400,atof(z_char)));

            delete[] x_char;
            delete[] y_char;
            delete[] z_char;
        }
        else if(line.Length() > 1 && line[0] == 'f' && line[1] == ' ')
        {
            List<String> list = line.Split(' ');
            List<int> faces;

            for(int i = 2; i<list.Size(); i++)
            {
                char* num = list[i].Split('/')[0].GetText();
                faces.Add(atoi(num));
                delete[] num;
            }

            faceList.Add(faces);
        }
    }

    input.close();

    std::fstream file("out1.svg", std::ios::out | std::ios::trunc);

    file<<"<svg height=\"900\" width=\"1600\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for(int x = 0; x<faceList.Size();x++)
    {
        file<<"\t<polygon points=\"";
        for(int y = 0; y<faceList[x].Size();y++)
        {
            file<<vectorList[faceList[x][y]-1].x<<","<<vectorList[faceList[x][y]-1].y<<" ";
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
        file<<"\t<circle r=\"3\" cx=\""<<vectorList[i].x<<"\" cy=\""<<vectorList[i].y<<"\" fill=\"#D900FF\" />\n";
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

