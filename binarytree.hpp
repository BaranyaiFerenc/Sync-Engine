#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP


template<typename T>
class BinaryTree
{
    struct Element
    {
        int id;
        T value;

        Element* left_child = 0;
        Element* right_child = 0;
    };

    Element* root = 0;

public:

    void Add()
    {

    }

};



#endif