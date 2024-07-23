#include "vector.h"

Vector Vector::operator+(const Vector& v) const
{
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const
{
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(double d) const
{
    return Vector(x * d, y * d, z * d);
}

Vector Vector::operator*(const Vector& v) const
{
    return Vector(x * v.x, y * v.y, z * v.z);
}

void Vector::operator=(const Vector& v)
{
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
}

void Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

double Vector::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::normalized() const
{
    double length = this->Length();
    return Vector(x / length, y / length, z / length);
}

Vector Vector::Round() const
{
    return Vector(int(x), int(y), int(z));
}

std::ostream& operator<<(std::ostream& os, const Vector v)
{
    os << "(" << v.x << "; " << v.y << "; " << v.z << ")";
    return os;
}


Face::Face(int *ids, size_t n):size(n)
{
    vertexIDs = new int[n];

    for(size_t i = 0; i<n; i++)
        vertexIDs[i] = ids[i];
}

Face::~Face()
{
    delete[] vertexIDs;
}

int Face::operator[](unsigned int idx) const
{
    if(idx < 0 || idx >= size)
        Logger::Log("Out of range - Face::operator[]()", Logger::error);

    return vertexIDs[idx];
}

int& Face::operator[](unsigned int idx)
{
    if(idx < 0 || idx >= size)
        Logger::Log("Out of range - Face::operator[]()", Logger::error);

    return vertexIDs[idx];
}

std::ostream& operator<<(std::ostream& os, const Face& face)
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