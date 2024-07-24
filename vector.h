#ifndef PRINTER_VECTOR_H
#define PRINTER_VECTOR_H


#include <iostream>
#include <cmath>


class Vector
{
public:

    double x,y,z;

    Vector(double xt = 0, double yt = 0, double zt = 0): x(xt), y(yt), z(zt) {}
    Vector(const Vector& v): x(v.x), y(v.y), z(v.z) {}

    Vector operator+(const Vector& v) const;

    Vector operator-(const Vector& v) const;

    Vector operator*(double d) const;

    Vector operator*(const Vector& v) const;

    void operator=(Vector v);

    void operator+=(const Vector& v);

    void operator-=(const Vector& v);

    double Length() const;

    Vector normalized() const;

    Vector Round() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector v);
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
    Face(int* ids, size_t n);

    size_t getSize() const {return size;}
    int operator[](unsigned int idx) const;
    int& operator[](unsigned int idx);

    ~Face();

    friend std::ostream& operator<<(std::ostream&, const Face&);
};



#endif //PRINTER_VECTOR_H