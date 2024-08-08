#ifndef SVGCREATOR_HPP
#define SVGCREATOR_HPP

#include "string.hpp"
#include "object.hpp"
#include "basiccamera.hpp"

#include "rgb.hpp"

#include <fstream>
#include <iostream>

class SvgCreator
{
    int width,heigth;
    String path;

public:

    SvgCreator(String path_, int width_ = 1600, int heigth_ = 900):path(path_), width(width_), heigth(heigth_){}


    double LightFalloff(double val)
    {
        double min = 0.5;

        if(val < 0)
            return min;

        double calc = val > 0.1286 ? (atan(20*val-1)/5)+0.599 : (sin(5*val)+1)/2;
        return calc;
    }

    void DrawSVG(const DinArray<Object>& objArray ,BasicCamera& cam)
    {
        double offset_x = 500;
        double offset_y = 300;

        std::fstream file(path.GetText(), std::ios::out | std::ios::trunc);

        file<<"<svg height=\""<<heigth<<"\" width=\""<<width<<"\" xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:gray\">\n";

    
        Vector lightSource(-5,3,2);
        Vector lightSourceCamPos = cam.GetScreenPoint(lightSource);

        file<<"<circle r=\"30\" cx=\""<<lightSourceCamPos.x+offset_x<<"\" cy=\""<<lightSourceCamPos.y+offset_y<<"\" fill=\"yellow\" />\n";

        Vector xStart = cam.GetScreenPoint(Vector(-1000,0,0));
        Vector xEnd = cam.GetScreenPoint(Vector(1000,0,0));

        file<<"<line x1=\""<<xStart.x+offset_x<<"\" y1=\""<<xStart.y+offset_y<<"\" x2=\""<<xEnd.x+offset_x<<"\" y2=\""<<xEnd.y+offset_y<<"\" style=\"stroke:red;stroke-width:4\" />\n";

        Vector yStart = cam.GetScreenPoint(Vector(0,-1000,0));
        Vector yEnd = cam.GetScreenPoint(Vector(0,1000,0));

        file<<"<line x1=\""<<yStart.x+offset_x<<"\" y1=\""<<yStart.y+offset_y<<"\" x2=\""<<yEnd.x+offset_x<<"\" y2=\""<<yEnd.y+offset_y<<"\" style=\"stroke:green;stroke-width:4\" />\n";

        
        Vector zStart = cam.GetScreenPoint(Vector(0,0,-1000));
        Vector zEnd = cam.GetScreenPoint(Vector(0,0,1000));

        file<<"<line x1=\""<<zStart.x+offset_x<<"\" y1=\""<<zStart.y+offset_y<<"\" x2=\""<<zEnd.x+offset_x<<"\" y2=\""<<zEnd.y+offset_y<<"\" style=\"stroke:blue;stroke-width:4\" />\n";

        for(int i = 0; i<objArray.Length(); i++)
        {
            
            Object obj = objArray[i];
            DinArray<Vector> projectedPoints = cam.ProjectObject(obj);


            for(int i = 0; i<obj.transform.mesh.faces.Length(); i++)
            {
                for(int k = 0; k<obj.transform.mesh.faces.Length()-i-1; k++)
                {
                    if((obj.transform.mesh.GetFacePivot(k)-cam.position).Length() < (obj.transform.mesh.GetFacePivot(k+1)-cam.position).Length())  
                    {
                        Face buff = obj.transform.mesh.faces[k];
                        obj.transform.mesh.faces[k] = obj.transform.mesh.faces[k+1];
                        obj.transform.mesh.faces[k+1] = buff;
                    }
                }
            }
            

            for(int x = 0; x<obj.transform.mesh.faces.Length();x++)
            {
                DinArray<Vector> facePoint = obj.transform.mesh.GetFaceVectors(x);

                file<<"\t<polygon points=\"";
                for(int y = 0; y<facePoint.Length();y++)
                {
                    Vector point = cam.GetScreenPoint(facePoint[y]);
                    file<<point.x+offset_x<<","<<point.y+offset_y<<" ";
                }

                Vector faceNormal = obj.transform.mesh.GetFaceNormal(x);
                Vector facePivot = obj.transform.mesh.GetFacePivot(x);
                
                Vector a = faceNormal-facePivot;
                Vector b = lightSource-facePivot;

                double rayAngle = a.GetAngle(b);

                double minLight = 10;

                double color = LightFalloff(rayAngle)*255;

                file<<"\" style=\"stroke:"<<"black"<<";stroke-width:0\" fill-opacity=\"1\" fill=\""<<RGB::rgbToHex(color,color,color)<<"\"/>\n";
            }

            for(int x = 0; x<obj.transform.mesh.faces.Length() && false;x++)
            {
                Vector facePivot = obj.transform.mesh.GetFacePivot(x);
                Vector normal = obj.transform.mesh.GetFaceNormal(x);

                Vector a = normal-facePivot;
                Vector b = lightSource-facePivot;

                Vector facePivotCamSpace = cam.GetScreenPoint(facePivot);
                Vector normalCamSpace = cam.GetScreenPoint(facePivot+b.normalized());


                double rayAngle = a.GetAngle(b);

                file<<"<text x=\""<<normalCamSpace.x+10+offset_x<<"\" y=\""<<normalCamSpace.y+10+offset_y<<"\" fill=\"red\">"<<rayAngle<<"</text>\n";

                file<<"<circle r=\"1\" cx=\""<<facePivotCamSpace.x+offset_x<<"\" cy=\""<<facePivotCamSpace.y+offset_y<<"\" fill=\"purple\" />\n";
                file<<"<line x1=\""<<facePivotCamSpace.x+offset_x<<"\" y1=\""<<facePivotCamSpace.y+offset_y<<"\" x2=\""<<normalCamSpace.x+offset_x<<"\" y2=\""<<normalCamSpace.y+offset_y<<"\" style=\"stroke:purple;stroke-width:1\" />\n";
            
            }



            Vector pivotToScreen = cam.GetScreenPoint(obj.transform.Pivot());
            file<<"<text x=\""<<pivotToScreen.x+offset_x<<"\" y=\""<<pivotToScreen.y+100+offset_y<<"\" fill=\"red\">"<<obj.name<<"</text>\n";
            file<<"<circle r=\"10\" cx=\""<<pivotToScreen.x+offset_x<<"\" cy=\""<<pivotToScreen.y+offset_y<<"\" fill=\"red\" />\n";
        }


    
        file<<"</svg>";

        file.close();
        
    }
};


#endif