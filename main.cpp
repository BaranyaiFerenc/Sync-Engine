#include "list.hpp"
#include <iostream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    List<int> list = List<int>();

    for(int i = 0; i<10; i++)
    {
        list.Add(i);
    }

    list.Sort(bigger);

    list.Print();
}

int main()
{
    run();

    return 0;
}

