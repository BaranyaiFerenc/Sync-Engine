#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vector.hpp"
#include "dinarray.hpp"

class Face
{
    DinArray<int> data;

public:

    Face(){}

    Face(const Face& face)
    {
        data = face.data;
    }

    void operator=(const Face& face)
    {
        data = face.data;
    }

    void AddVector(const int& toAdd)
    {
        data.Add(toAdd);
    }

    int operator[](unsigned int index) const
    {
        return data[index];
    }

    int& operator[](unsigned int index)
    {
        return data[index];
    }

    unsigned int Count() const {return data.Length();}
};

class Mesh
{
public:

    DinArray<Vector> vertices;
    DinArray<Face> faces;

    DinArray<Vector> calculatedVertices;

    Mesh():vertices(DinArray<Vector>(600)), faces(DinArray<Face>(600)){}


    Vector GetFacePivot(unsigned int faceIndex) const
    {
        Face choosen = faces[faceIndex];

        double sumX = 0;
        double sumY = 0; 
        double sumZ = 0;

        int n = choosen.Count();

        for(int i = 0; i<n; i++)
        {
            sumX += calculatedVertices[choosen[i]].x;
            sumY += calculatedVertices[choosen[i]].y;
            sumZ += calculatedVertices[choosen[i]].z;
        }

        return Vector(sumX/n, sumY/n, sumZ/n);
    }

    Vector GetFaceNormal(unsigned int faceIndex) const
    {
        Face choosen = faces[faceIndex];

        Vector a = calculatedVertices[choosen[1]]-calculatedVertices[choosen[0]];
        Vector b = calculatedVertices[choosen[2]]-calculatedVertices[choosen[0]];

        Vector normal;

        normal.x = a.y*b.z-a.z*b.y;
        normal.y = a.z*b.x-a.x*b.z;
        normal.z = a.x*b.y-a.y*b.x;

        return normal;
    }

    DinArray<Vector> GetFaceVectors(unsigned int faceIndex) const
    {
        DinArray<Vector> result;

        Face choosen = faces[faceIndex];

        for(int i = 0; i<choosen.Count(); i++)
        {
            result.Add(calculatedVertices[choosen[i]]);
        }

        return result;
    }
};

class Transform
{
    Vector position;
    Vector scale;
    Rotation rotation;
public:


    Mesh mesh;

    Transform()
    {
        scale = Vector(1,1,1);
        position = Vector();
        rotation = Rotation();
    }

    void RefreshMesh()
    {
        DinArray<Vector> result;
        for(int i = 0; i<mesh.vertices.Length(); i++)
        {
            result.Add(GetVertex(i));
        }

        mesh.calculatedVertices = result;
    }

    void Move(const Vector& moveVector)
    {
        position += moveVector;
        RefreshMesh();
    }

    void Rotate(const Rotation& rot)
    {
        rotation+=rot;
        RefreshMesh();
    }

    void SetPosition(const Vector& pos)
    {
        position = pos;
        RefreshMesh();
    }

    void SetRotation(const Rotation& rot)
    {
        rotation = rot;
        RefreshMesh();
    }

    void SetScale(const Vector& sc)
    {
        scale = sc;
        RefreshMesh();
    }


    Vector Pivot() const
    {
        double sumX = 0;
        double sumY = 0; 
        double sumZ = 0;

        int n = mesh.vertices.Length();

        for(int i = 0; i<n; i++)
        {
            sumX += mesh.vertices[i].x;
            sumY += mesh.vertices[i].y;
            sumZ += mesh.vertices[i].z;
        }

        return Vector(sumX/n, sumY/n, sumZ/n);
    }

    Vector GetVertex(unsigned int index) const
    {
        Vector pivot = Pivot();

        Vector vert = mesh.vertices[index]-pivot;
        vert = vert.Rotate(rotation);
        vert.x = vert.x*scale.x;
        vert.y = vert.y*scale.y;
        vert.z = vert.z*scale.z;
        return (vert+position+pivot);
    }

};



#endif