#include "list.hpp"
#include <iostream>



int main()
{
    List<int> list = List<int>();

    for(int i = 0; i<10; i++)
    {
        list.Add(i);
    }

    list.Print();

    list[2] = 128;
    list.RemoveAt(4);
    
    list.Print();

    std::cout<<"Size: "<<list.Size();

    
    for(int i = 0; i<10; i++)
    {
        list.Add(i);
    }

    
    for(int i = 0; i<10; i++)
    {
        list.Add(i);
    }

    list.Print();

    list.Remove(1, true);

    
    list.Print();

    return 0;
}
