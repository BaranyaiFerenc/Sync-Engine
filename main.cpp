#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"

#include <iostream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    


    int x = 100;
    int y = 100;

    Matrix mx1(x,y);
    Matrix mx2(x,y);

    for(int i = 0; i<x; i++)
    {
        for(int k = 0; k<y; k++)
        {
            mx1[i][k] = i*x+k;
            mx2[i][k] = i*x+k;
        }
    }

    mx1.PrintMultiplication(mx2);
}

int main()
{
    run();

    return 0;
}

