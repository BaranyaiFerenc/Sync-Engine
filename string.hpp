#include "list.hpp"
#include <iostream>

class String
{

    List<char> data;

public:

    void operator=(char c)
    {
        data.Add(c);
        data.Add('\0');
    }

    void operator=(char* str)
    {
        for(int i = 0; str[i] != '\0'; i++)
        {
            data.Add(str[i]);
        }
        data.Add('\0');
    }
    
    void operator=(String str)
    {
        data = str.data;
    }

    friend std::ostream& operator<<(std::ostream& os, String str)
    {
        for(int i = 0; i<str.data.Size(); i++)
        {
            os<<str.data[i];
        }

        return os;
    }
};