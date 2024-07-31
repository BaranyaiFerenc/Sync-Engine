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

    BasicCamera cam;
    cam.far = 5000;
    cam.near = 0.1;
    cam.fov = 70;
    cam.position = Vector(0,3,10);
    cam.resulotion = Vector(1600,900);
    cam.rotation = Rotation(0,0,0);

    DinArray<Object> obj = Import::ImportObj("sample/Donuts.obj");
    std::cout<<"Object count: "<<obj.Length()<<std::endl;

    for(int i = 0; i<obj.Length(); i++)
    {
        std::cout<<obj[i].name<<std::endl;
        std::cout<<"\t"<<obj[i].transform.mesh.vertices.Length()<<std::endl;
    }

    //obj[0].transform.position = Vector(1,1,1);

    for(int i = 0; i<=0; i++)
    {
        String path = "video/Donut/outdraw";
        path += std::to_string(i).c_str();
        path += ".svg";

        SvgCreator svg(path);
        svg.DrawSVG(obj, cam);
        
        for(int k = 0; k<obj.Length(); k++)
        {
            obj[k].transform.rotation.Rotate(Vector(1,1,1));
        }
    }

    
    Logger logger(std::cout, "main.cpp");

    logger.ConsoleLog("Calculations are done");
}

#include "stopper.hpp"
#include "dinarray.hpp"


void DinTest()
{
    DinArray<int> lista;

    int n = 600;
    for(int i = 0; i<n; i++)
    {
        lista.Add(i);
    }

    
    for(int i = 0; i<n; i++)
        int a = lista[i];
}

void ListTest()
{
    List<int> lista;
    int n = 600;

    for(int i = 0; i<n; i++)
    {
        lista.Add(i);
    }

    for(int i = 0; i<n; i++)
        int a = lista[i];
}

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    int testCount = 1;

    std::fstream file("test_numbers.txt",std::ios::out | std::ios::trunc);

    auto t1 = high_resolution_clock::now();

    for(int i = 0; i < testCount; i++)
    {
        run();
    }

    auto t2 = high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto ms_int = duration_cast<milliseconds>(t2 - t1).count();

    std::cout << ms_int << std::endl;

    file.close();

    return 0;
}

