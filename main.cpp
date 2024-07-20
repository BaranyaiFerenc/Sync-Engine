#include "string.hpp"
#include <iostream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    String str;
    str = "Hello World";

    std::cout<<str;
}

int main()
{
    run();

    return 0;
}

