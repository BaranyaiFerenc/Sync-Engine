#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "vector.hpp"
#include "list.hpp"


class Transform
{
public:

    Vector position;
    Rotation rotation;


    void Move(const Vector& moveVector)
    {
        position += moveVector;
    }

    void Rotate(const Rotation& rot)
    {
        rotation+=rot;
    }
};


class Mesh
{
public:

    List<Vector> vertices;
    List<List<int>> faces;
};

#endif