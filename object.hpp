#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "vector.hpp"
#include "list.hpp"
#include "string.hpp"
#include "transform.hpp"

class Object
{

public:
    String name;
    long int id;
    Transform transform;
};


#endif