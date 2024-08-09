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
        double offset_x = 0;
        double offset_y = 0;

        std::fstream file(path.GetText(), std::ios::out | std::ios::trunc);

        file<<"<svg height=\""<<heigth<<"\" width=\""<<width<<"\" xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:gray\">\n";

    
        Vector lightSource(-5,5,2);
        Vector lightSourceCamPos = cam.GetScreenPoint(lightSource);

        for(int x = -10; x < 10; x++)
        {
            Vector linePosStart = cam.GetScreenPoint(Vector(x,0,cam.position.z));
            Vector linePosEnd = cam.GetScreenPoint(Vector(x, 0, cam.position.z+cam.far));
            file<<"<line x1=\""<<linePosStart.x<<"\" y1=\""<<linePosStart.y<<"\" x2=\""<<linePosEnd.x<<"\" y2=\""<<linePosEnd.y<<"\" style=\"stroke:#A3A2A2;stroke-width:2\" />\n";

            
            Vector numbering = cam.GetScreenPoint(Vector(x, 0, 0));
            
            file<<"<text x=\""<<numbering.x+10<<"\" y=\""<<numbering.y+10<<"\" fill=\"red\">"<<x<<"</text>\n";

            numbering = cam.GetScreenPoint(Vector(0, 0, x));
            
            file<<"<text x=\""<<numbering.x+10<<"\" y=\""<<numbering.y+10<<"\" fill=\"red\">"<<x<<"</text>\n";
            
            linePosStart = cam.GetScreenPoint(Vector(cam.GetLeftBorder(x).x,0,x));
            linePosEnd = cam.GetScreenPoint(Vector(cam.GetRightBorder(x).x, 0, x));
            file<<"<line x1=\""<<linePosStart.x<<"\" y1=\""<<linePosStart.y<<"\" x2=\""<<linePosEnd.x<<"\" y2=\""<<linePosEnd.y<<"\" style=\"stroke:#A3A2A2;stroke-width:2\" />\n";

        }

        //file<<"<circle r=\"30\" cx=\""<<lightSourceCamPos.x+offset_x<<"\" cy=\""<<lightSourceCamPos.y+offset_y<<"\" fill=\"yellow\" />\n";

        Vector xStart = cam.GetScreenPoint(cam.GetLeftBorder(0));
        Vector xEnd = cam.GetScreenPoint(cam.GetRightBorder(0));

        file<<"<line x1=\""<<xStart.x<<"\" y1=\""<<xStart.y<<"\" x2=\""<<xEnd.x<<"\" y2=\""<<xEnd.y<<"\" style=\"stroke:red;stroke-width:4\" />\n";

        Vector yStart = cam.GetScreenPoint(cam.GetBottomBorder(0));
        Vector yEnd = cam.GetScreenPoint(cam.GetTopBorder(0));

        file<<"<line x1=\""<<yStart.x<<"\" y1=\""<<yStart.y<<"\" x2=\""<<yEnd.x<<"\" y2=\""<<yEnd.y<<"\" style=\"stroke:green;stroke-width:4\" />\n";

        
        Vector zStart = cam.GetScreenPoint(Vector(0,0,cam.position.z));
        Vector zEnd = cam.GetScreenPoint(Vector(0,0,cam.far+cam.position.z));

        file<<"<line x1=\""<<zStart.x<<"\" y1=\""<<zStart.y<<"\" x2=\""<<zEnd.x<<"\" y2=\""<<zEnd.y<<"\" style=\"stroke:blue;stroke-width:4\" />\n";




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
                    file<<point.x<<","<<point.y<<" ";
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

                file<<"<text x=\""<<normalCamSpace.x+10<<"\" y=\""<<normalCamSpace.y+10<<"\" fill=\"red\">"<<rayAngle<<"</text>\n";

                file<<"<circle r=\"1\" cx=\""<<facePivotCamSpace.x<<"\" cy=\""<<facePivotCamSpace.y<<"\" fill=\"purple\" />\n";
                file<<"<line x1=\""<<facePivotCamSpace.x<<"\" y1=\""<<facePivotCamSpace.y<<"\" x2=\""<<normalCamSpace.x<<"\" y2=\""<<normalCamSpace.y<<"\" style=\"stroke:purple;stroke-width:1\" />\n";
            
            }



            Vector pivotToScreen = cam.GetScreenPoint(obj.transform.Pivot());
            file<<"<text x=\""<<pivotToScreen.x<<"\" y=\""<<pivotToScreen.y+100<<"\" fill=\"red\">"<<obj.name<<"</text>\n";
            file<<"<circle r=\"10\" cx=\""<<pivotToScreen.x<<"\" cy=\""<<pivotToScreen.y<<"\" fill=\"red\" />\n";
        }


    
        file<<"</svg>";

        file.close();
        
    }
};


#endif