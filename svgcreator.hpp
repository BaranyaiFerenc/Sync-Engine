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

    void DrawSVG(const DinArray<Object>& objArray ,BasicCamera& cam)
    {
        double offset_x = 500;
        double offset_y = 300;

        std::fstream file(path.GetText(), std::ios::out | std::ios::trunc);

        file<<"<svg height=\""<<heigth<<"\" width=\""<<width<<"\" xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:white\">\n";

    
        Vector lightSource(-5,3,0);
        Vector lightSourceCamPos = cam.GetScreenPoint(lightSource);

        file<<"<circle r=\"30\" cx=\""<<lightSourceCamPos.x+offset_x<<"\" cy=\""<<lightSourceCamPos.y+offset_y<<"\" fill=\"yellow\" />\n";

        for(int i = 0; i<objArray.Length(); i++)
        {
            
            Object obj = objArray[i];
            DinArray<Vector> projectedPoints = cam.ProjectObject(obj);


            for(int i = 0; i<obj.transform.mesh.faces.Length(); i++)
            {
                for(int k = 0; k<obj.transform.mesh.faces.Length()-1; k++)
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

                file<<"\" style=\"stroke:"<<"black"<<";stroke-width:1\" fill-opacity=\"1\" fill=\""<<RGB::rgbToHex(rayAngle*255,rayAngle*255,rayAngle*255)<<"\"/>\n";
            }

            for(int x = 0; x<obj.transform.mesh.faces.Length();x++)
            {
                Vector facePivot = obj.transform.mesh.GetFacePivot(x);
                Vector normal = obj.transform.mesh.GetFaceNormal(x);

                Vector facePivotCamSpace = cam.GetScreenPoint(facePivot);
                Vector normalCamSpace = cam.GetScreenPoint(facePivot+normal.normalized());

                Vector a = normal-facePivot;
                Vector b = lightSource-facePivot;

                double rayAngle = a.GetAngle(b);

                file<<"<text x=\""<<facePivotCamSpace.x+offset_x<<"\" y=\""<<facePivotCamSpace.y+10+offset_y<<"\" fill=\"red\">"<<rayAngle<<"</text>\n";

                file<<"<circle r=\"10\" cx=\""<<facePivotCamSpace.x+offset_x<<"\" cy=\""<<facePivotCamSpace.y+offset_y<<"\" fill=\"purple\" />\n";
                file<<"<line x1=\""<<facePivotCamSpace.x+offset_x<<"\" y1=\""<<facePivotCamSpace.y+offset_y<<"\" x2=\""<<normalCamSpace.x+offset_x<<"\" y2=\""<<normalCamSpace.y+offset_y<<"\" style=\"stroke:purple;stroke-width:4\" />\n";
            
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