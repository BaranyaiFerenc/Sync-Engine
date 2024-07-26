#ifndef STOPPER_HPP
#define STOPPER_HPP

#include <iostream>
#include <time.h>

class Stopper
{
    long int startTime;

public:

    void Set()
    {
        startTime = static_cast<long int> (time(NULL));
    }

    long int Stop()
    {
        return static_cast<long int> (time(NULL))-startTime;
    }

};

#endif