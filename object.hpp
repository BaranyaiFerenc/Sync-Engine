#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "vector.hpp"
#include "list.hpp"
#include "string.hpp"
#include "components.hpp"

class Object
{

public:
    String name;
    long int id;
    Transform transform;
    Mesh mesh;
};


#endif