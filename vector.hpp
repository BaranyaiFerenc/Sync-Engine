#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>

#include "matrix.hpp"


class Vector
{
public:

    double x,y,z;

    Vector(double xt = 0, double yt = 0, double zt = 0): x(xt), y(yt), z(zt) {}
    Vector(const Vector& v): x(v.x), y(v.y), z(v.z){}

    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector operator*(double d) const
    {
        return Vector(x * d, y * d, z * d);
    }

    Vector operator*(const Vector& v) const
    {
        return Vector(x * v.x, y * v.y, z * v.z);
    }

    Vector& operator=(const Vector& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    bool operator==(const Vector& v)
    {
        return x==v.x && y == v.y && z == v.z;
    }
    bool operator!=(const Vector& v)
    {
        return !(x==v.x && y == v.y && z == v.z);
    }

    void operator+=(const Vector& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void operator-=(const Vector& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    double Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector normalized() const
    {
        double length = this->Length();

        if(length == 0)
            return Vector(0,0,0);

        return Vector(x / length, y / length, z / length);
    }

    Vector Round() const
    {
        return Vector(int(x), int(y), int(z));
    }

    Vector RotateX(double rad)
    {
        Vector result(x,y,z);

        result.x = result.x;
        result.y = cos(rad)*result.y+(-sin(rad)*result.z);
        result.z = sin(rad)*result.y+cos(rad)*result.z;

        return result;
    }

    Vector RotateY(double rad)
    {
        Vector result(x,y,z);

        result.x = cos(rad)*result.x+sin(rad)*result.z;
        result.y = result.y;
        result.z = (-sin(rad)*result.x)+cos(rad)*result.z;

        return result;
    }
    Vector RotateZ(double rad)
    {
        Vector result(x,y,z);

        result.x = cos(rad)*result.x+(-sin(rad)*result.y);
        result.y = sin(rad)*result.x+cos(rad)*result.y;
        result.z = result.z;

        return result;
    }

    Vector Rotate(Vector rad) const
    {
        
        Matrix vector(3,1);
        vector[0][0] = x;
        vector[1][0] = y;
        vector[2][0] = z;
/*
        Vector result(x,y,z);


        result.x = result.x;
        result.y = cos(rad.x)*result.y+(-sin(rad.x)*result.z);
        result.z = sin(rad.x)*result.y+cos(rad.x)*result.z;
        
        result.x = cos(rad.y)*result.x+sin(rad.y)*result.z;
        result.y = result.y;
        result.z = (-sin(rad.y)*result.x)+cos(rad.y)*result.z;

        result.x = cos(rad.z)*result.x+(-sin(rad.z)*result.y);
        result.y = sin(rad.z)*result.x+cos(rad.z)*result.y;
        result.z = result.z;

        double zk = result.z;


        ///Rotate on x
        Matrix xRot(3,3);
        xRot[0][0] = 1;
        xRot[1][1] = cos(rad.x);
        xRot[1][2] = -sin(rad.x);
        xRot[2][1] = sin(rad.x);
        xRot[2][2] = cos(rad.x);

        vector = xRot*vector;



        ///Rotate on y
        Matrix yRot(3,3);
        yRot[0][0] = cos(rad.y);
        yRot[0][2] = sin(rad.y);
        yRot[1][1] = 1;
        yRot[2][0] = -sin(rad.y);
        yRot[2][2] = cos(rad.y);

        vector = yRot*vector;

        
        std::cout<<zk<<"  ->  "<<vector[2][0]<<std::endl;


        ///Rotate on z
        Matrix zRot(3,3);
        zRot[0][0] = cos(rad.z);
        zRot[0][1] = -sin(rad.z);
        zRot[1][0] = sin(rad.z);
        zRot[1][1] = cos(rad.z);
        zRot[2][2] = 1;

        vector = zRot*vector;*/

        Matrix rotMatrix(3,3);
        rotMatrix[0][0] = cos(rad.y)*cos(rad.z);
        rotMatrix[0][1] = sin(rad.x)*sin(rad.y)*cos(rad.z)-cos(rad.x)*sin(rad.z);
        rotMatrix[0][2] = cos(rad.x)*sin(rad.y)*cos(rad.z)+sin(rad.x)*sin(rad.z);

        rotMatrix[1][0] = cos(rad.y)*sin(rad.z);
        rotMatrix[1][1] = sin(rad.x)*sin(rad.y)*sin(rad.z)+cos(rad.x)*cos(rad.z);
        rotMatrix[1][2] = cos(rad.x)*sin(rad.y)*sin(rad.z)-sin(rad.x)*cos(rad.z);

        rotMatrix[2][0] = -sin(rad.y);
        rotMatrix[2][1] = sin(rad.x)*cos(rad.y);
        rotMatrix[2][2] = cos(rad.x)*cos(rad.y);

        vector = rotMatrix*vector;

        Vector end = Vector(vector[0][0], vector[1][0], vector[2][0]);
/*
        if(end != result)
        {
            std::cout<<rad<<" ---> "<<end<<" wrong----> "<<result<<std::endl;
        }
        else
        {
            std::cout<<rad<<" ---> "<<end<<" good----> "<<result<<std::endl;
        }*/

        return end;
    }   

    friend std::ostream& operator<<(std::ostream& os, const Vector v)
    {
        os << "(" << v.x << "; " << v.y << "; " << v.z << ")";
        return os;
    }
};

class Rotation: public Vector
{
public:
    Rotation(double x = 0, double y = 0, double z = 0): Vector(x,y,z){}

    Vector GetRadVector() const
    {
        double convert = M_PI/180;
        return Vector(x*convert,y*convert, z*convert);
    }

    void RotateY(double deg)
    {
        y += deg*(M_PI/180);
    }
};


class Face
{
    int* vertexIDs;
    size_t size;

public:
    Face():size(0){}
    Face(int* ids, size_t n)
    {
        vertexIDs = new int[n];

        for(size_t i = 0; i<n; i++)
            vertexIDs[i] = ids[i];
    }

    size_t getSize() const {return size;}

    int operator[](unsigned int idx) const
    {
        return vertexIDs[idx];
    }

    int& operator[](unsigned int idx)
    {
        return vertexIDs[idx];
    }

    ~Face()
    {
        delete[] vertexIDs;
    }

    friend std::ostream& operator<<(std::ostream& os, const Face& face)
    {
        os<<"(";
        for(unsigned int i = 0; i<face.size; i++)
        {
            if(i+1 != face.size)
                os<<face[i]<<"/";
            else
                os<<face[i]<<")";
        }

        return os;
    }
};



#endif //PRINTER_VECTOR_H