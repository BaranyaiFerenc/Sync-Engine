#ifndef STRING_HPP
#define STRING_HPP

#include "list.hpp"
#include <iostream>

class String
{

    List<char> data;

public:

    String()
    {

    }

    String(char* str)
    {
        *this = str;
    }

    char* GetText() const
    {
        char* text = new char[data.Size()+1];

        for(int i = 0; i<data.Size(); i++)
        {
            text[i] = data[i];
        }

        text[data.Size()] = '\0';

        return text;
    }

    unsigned int Length() const
    {
        return data.Size();
    }


    void operator=(char c)
    {
        data.Clear();
        data.Add(c);
    }
    void operator=(String str)
    {
        data.Clear();
        data = str.data;
    }

    void operator=(char* str)
    {
        data.Clear();

        for(int i = 0; str[i] != '\0'; i++)
        {
            data.Add(str[i]);
        }
    }

    void operator+=(char c)
    {
        data.Add(c);
    }

    void operator+=(char* str)
    {
        for(int i = 0; str[i] != '\0'; i++)
        {
            data.Add(str[i]);
        }
    }

    void operator+=(String str)
    {
        data.Add(str.data);
    }
    

    char operator[](unsigned int index) const
    {
        return data[index];
    }
    
    char& operator[](unsigned int index)
    {
        return data[index];
    }

    void Clear()
    {
        data.Clear();
    }

    List<String> Split(char sep) const
    {
        List<String> result = List<String>();
        String actual;

        for(int i = 0; i<data.Size(); i++)
        {
            if(data[i] != sep)
            {
                actual+=data[i];
            }
            else
            {
                result.Add(actual);
                actual.Clear();
            }
        }

        result.Add(actual);

        return result;
    }

    void RemoveAt(unsigned int index)
    {
        data.RemoveAt(index);
    }

    void RemoveAt(unsigned int startIncluded, unsigned int endExcluded)
    {
        for(int i = startIncluded; i<endExcluded; i++)
        {
            data.RemoveAt(startIncluded);
        }
    }

    void Replace(char* from, char* to)
    {
        List<char> result = List<char>();

        unsigned int len = 0;
        for(int x = 0; from[x] != '\0'; x++)
        {
            len++;
        }

        for(int i = 0; i<data.Size()-len; i++)
        {
            bool find = true;
            for(int x = 0; from[x] != '\0'; x++)
            {
                if(from[x] != data[i+x])
                {
                    find = false;
                    break;
                }
            }

            if(find == true)
            {
                for(int x = 0; to[x] != '\0'; x++)
                {
                    result.Add(to[x]);
                }
                
                i+=(len-1);
            }
            else
            {
                result.Add(data[i]);
            }
        }

        for(int i = data.Size()-len; i<data.Size(); i++)
        {
            result.Add(data[i]);
        }

        data = result;
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


#endif