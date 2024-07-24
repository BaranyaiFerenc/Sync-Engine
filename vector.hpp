#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>


class Vector
{
public:

    double x,y,z;

    Vector(double xt = 0, double yt = 0, double zt = 0): x(xt), y(yt), z(zt) {}
    Vector(const Vector& v): x(v.x), y(v.y), z(v.z) {}

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
        return Vector(x / length, y / length, z / length);
    }

    Vector Round() const
    {
        return Vector(int(x), int(y), int(z));
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