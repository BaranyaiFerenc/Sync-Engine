#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include <iostream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    Dictionary<int, double> dict;
    dict.Add(1, 2.4);
    dict.Add(10, 5.6);
    dict.Add(255, 104.9);

    dict[255] = 99.99;

    dict.Print();
}

int main()
{
    run();

    return 0;
}

