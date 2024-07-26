#ifndef BASICCAMERA_HPP
#define BASICCAMERA_HPP

#include "vector.hpp"
#include "list.hpp"
#include "object.hpp"

#include <iostream>
#include <math.h>

class BasicCamera
{
public:
    double far,near;
    double fov;
    
    Vector resulotion;

    Vector position;
    Rotation rotation;

    Vector WorldToCamPosition(Vector worldPoint) const
    {
        Vector relativePos = (worldPoint-position);

        return relativePos.Rotate(rotation.GetRadVector());
    }



    Vector GetScreenPoint(const Vector& worldPoint) const
    {
        double focalLength = far-near;

        double angle = ((fov/2)*(M_PI/180));

        double right = focalLength/(cos(angle)/sin(angle));
        double left = -right;
        
        double top = right/(resulotion.x / resulotion.y);
        double bottom = -top;

        //std::cout<<"Right: "<<right<<", Left: "<<left<<", Top: "<<top<<", Bottom"<<bottom<<std::endl;


        Vector directionVector = WorldToCamPosition(worldPoint).normalized();

        //std::cout<<directionVector<<std::endl;

        Vector screenPoint = directionVector*(far/directionVector.z);

        //std::cout<<screenPoint<<std::endl;

        double scaleFactor = resulotion.x/(right*2);
        screenPoint.x = screenPoint.x * scaleFactor;
        screenPoint.y = screenPoint.y * scaleFactor;

        return screenPoint;
    }

    List<Vector> ProjectObject(Object obj) const
    {
        List<Vector> pointList;
        for(int i = 0; i<obj.mesh.vertices.Size(); i++)
        {
            Vector actual = obj.mesh.vertices[i];
            pointList.Add(actual);
        }

        return pointList;
    }

};

#endif