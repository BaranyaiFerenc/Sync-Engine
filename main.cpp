#include "string.hpp"
#include "list.hpp"
#include <iostream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    String str = "Hello World hogy vagy faszi? hogy vagy hogy talan";

    str.RemoveAt(3,7);

    str.Split(' ').Print();
}

int main()
{
    run();

    return 0;
}

