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
    Matrix mx1(2,2);

    mx1[0][0] = 1;
    mx1[0][1] = 2;
    mx1[1][0] = 3;
    mx1[1][1] = 4;


    
    Matrix mx2(2,2);

    mx2[0][0] = 1;
    mx2[0][1] = 2;
    mx2[1][0] = 3;
    mx2[1][1] = 4;



    mx2.Print(true);
    
    mx1.Print();

    Matrix result= (mx1*mx2);
    result.Print();
}

int main()
{
    run();

    return 0;
}

