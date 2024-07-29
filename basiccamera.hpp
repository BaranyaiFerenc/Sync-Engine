#ifndef BASICCAMERA_HPP
#define BASICCAMERA_HPP

#include "vector.hpp"
#include "list.hpp"
#include "object.hpp"

#include <iostream>
#include <math.h>

class BasicCamera
{

    double focalLength;

    double angle;

    double right;
    double left;
    
    double top;
    double bottom;

    double scaleFactor;

public:
    double far,near;
    double fov;
    
    Vector resulotion;

    Vector position;
    Rotation rotation;


    void CalculateSettings()
    {
        focalLength = far-near;

        angle = ((fov/2)*(M_PI/180));

        right = focalLength/(cos(angle)/sin(angle));
        left = -right;
        
        top = right/(resulotion.x / resulotion.y);
        bottom = -top;

        scaleFactor = resulotion.x/(right*2);
    }

    Vector WorldToCamPosition(Vector worldPoint) const
    {
        Vector relativePos = (worldPoint-position);

        return relativePos.Rotate(rotation.GetRadVector());
    }



    Vector GetScreenPoint(const Vector& worldPoint, bool settingUp = true)
    {
        if(settingUp)
        {
            CalculateSettings();
        }

        //std::cout<<"Right: "<<right<<", Left: "<<left<<", Top: "<<top<<", Bottom"<<bottom<<std::endl;


        Vector directionVector = WorldToCamPosition(worldPoint).normalized();

        //std::cout<<directionVector<<std::endl;

        Vector screenPoint = directionVector*(far/directionVector.z);

        //std::cout<<screenPoint<<std::endl;

        
        screenPoint.x = screenPoint.x * scaleFactor;
        screenPoint.y = screenPoint.y * scaleFactor;

        return screenPoint;
    }

    DinArray<Vector> ProjectObject(Object obj)
    {
        DinArray<Vector> pointList(600);
        for(int i = 0; i<obj.transform.mesh.vertices.Length(); i++)
        {
            Vector actual = GetScreenPoint(obj.transform.GetVertex(i),(i==0));
            pointList.Add(actual);
        }

        return pointList;
    }

};

#endif