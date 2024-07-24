#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include "list.hpp"

#include <iostream>

class Camera
{
public:
    Vector position;
    Rotation rotation;


    Vector resulotion;
    Vector sensorSize;
    double focalLength;
    double skew;


    Matrix CreateProjectionMatrix() const
    {
        Matrix mx1(4,4);
        mx1[0][0] = (focalLength*resulotion.x)/(2*sensorSize.x);
        mx1[0][1] = skew;
        mx1[1][1] = (focalLength*resulotion.y)/(2*sensorSize.y);
        mx1[2][1] = -1;
        mx1[2][2] = 1;
        mx1[3][3] = 1;

        Matrix mx2(4,4);
        mx2[0][0] = 1;
        mx2[1][1] = cos(rotation.x);
        mx2[1][2] = -sin(rotation.x);
        mx2[2][1] = sin(rotation.x);
        mx2[2][2] = cos(rotation.x);
        mx2[3][3] = 1;

        Matrix mx3(4,4);
        mx3[0][0] = cos(rotation.y);
        mx3[0][1] = sin(rotation.y);
        mx3[1][1] = 1;
        mx3[2][0] = -sin(rotation.y);
        mx3[2][1] = cos(rotation.y);
        mx3[2][2] = 1;
        mx3[3][3] = 1;

        Matrix mx4(4,4);
        mx4[0][0] = cos(rotation.z);
        mx4[0][1] = -sin(rotation.z);
        mx4[1][0] = sin(rotation.z);
        mx4[1][1] = cos(rotation.z);
        mx4[2][2] = 1;
        mx4[3][3] = 1;

        Matrix mx5(4,4);
        mx5[0][0] = 1;
        mx5[0][3] = -position.x;
        mx5[1][1] = 1;
        mx5[1][3] = -position.y;
        mx5[2][2] = 1;
        mx5[2][3] = -position.z;
        mx5[3][3] = 1;


        return (((mx1*mx2)*mx3)*mx4)*mx5;
    }


    void PrintMatrix() const
    {
        CreateProjectionMatrix().Print();
    }

    Vector CalculateScreenPoints(const Vector p) const
    {
        Matrix pointMatrix(4,1);
        pointMatrix[0][0] = p.x;
        pointMatrix[1][0] = p.y;
        pointMatrix[2][0] = p.z;
        pointMatrix[3][0] = 1;

        Matrix newMx = (CreateProjectionMatrix()*pointMatrix);

        Matrix perspectiveMatrix(4,4);
        perspectiveMatrix[0][0] = 1/newMx[2][0];
        perspectiveMatrix[1][1] = 1/newMx[2][0];
        perspectiveMatrix[2][2] = 1;
        perspectiveMatrix[2][2] = 1;

        Matrix result = perspectiveMatrix*newMx;

        return Vector(result[0][0],result[1][0],result[2][0]);
    }
};

#endif