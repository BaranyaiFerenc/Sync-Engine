#ifndef SVGCREATOR_HPP
#define SVGCREATOR_HPP

#include "string.hpp"
#include "object.hpp"
#include "basiccamera.hpp"

#include <fstream>
#include <iostream>

class SvgCreator
{
    int width,heigth;
    String path;

public:

    SvgCreator(String path_, int width_ = 1600, int heigth_ = 900):path(path_), width(width_), heigth(heigth_){}

    void DrawSVG(const Object& obj, BasicCamera& cam)
    {
        double offset_x = 500;
        double offset_y = 300;

        std::fstream file(path.GetText(), std::ios::out | std::ios::trunc);

        file<<"<svg height=\""<<heigth<<"\" width=\""<<width<<"\" xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:white\">\n";

        DinArray<Vector> projectedPoints = cam.ProjectObject(obj);

        for(int x = 0; x<obj.transform.mesh.faces.Length();x++)
        {
            file<<"\t<polygon points=\"";
            for(int y = 0; y<obj.transform.mesh.faces[x].Length();y++)
            {
                file<<projectedPoints[obj.transform.mesh.faces[x][y]].x+offset_x<<","<<projectedPoints[obj.transform.mesh.faces[x][y]].y+offset_y<<" ";
            }

            file<<"\" style=\"stroke:"<<"black"<<";stroke-width:3\" fill-opacity=\"0.1\"/>\n";
        }

    
        file<<"</svg>";

        file.close();
        
    }
};


#endif