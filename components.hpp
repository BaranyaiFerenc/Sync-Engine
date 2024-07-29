#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "vector.hpp"
#include "dinarray.hpp"



class Mesh
{
public:

    DinArray<Vector> vertices;
    DinArray<DinArray<int>> faces;

    Mesh():vertices(DinArray<Vector>(600)), faces(DinArray<DinArray<int>>(600)){}
};

class Transform
{
public:

    Vector position;
    Vector scale;
    Rotation rotation;

    Mesh mesh;

    Transform()
    {
        scale = Vector(1,1,1);
        position = Vector();
        rotation = Rotation();
    }


    void Move(const Vector& moveVector)
    {
        position += moveVector;
    }

    void Rotate(const Rotation& rot)
    {
        rotation+=rot;
    }

    Vector GetVertex(unsigned int index) const
    {
        Vector vert = mesh.vertices[index]+position;
        vert = vert.Rotate(rotation);
        vert = vert*scale;
        return vert;
    }
};

#endif