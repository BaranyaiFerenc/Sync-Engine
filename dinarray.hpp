#ifndef DINARRAY_HPP
#define DINARRAY_HPP

#include <iostream>

template<typename T>
class DinArray
{
    T* data;
    unsigned int length;
    unsigned int capacity;

    unsigned int threshold;

public:

    DinArray():length(0), capacity(20), threshold(20)
    {
        data = new T[20];
    }

    DinArray(unsigned int thr):length(0), capacity(thr), threshold(thr)
    {
        data = new T[thr];
    }

    DinArray(const DinArray<T>& array)
    {
        capacity = array.capacity;
        threshold = array.threshold;
        length = array.length;

        data = new T[capacity];
        

        for(int i = 0; i<array.length; i++)
        {
            data[i] = array.data[i];
        }
    }

    unsigned int Length() const {return length;}

    void Add(const T& element)
    {   
        if(length >= capacity)
        {
            capacity+=threshold;
            T* newData = new T[capacity];

            for(int i = 0; i<length; i++)
            {
                newData[i] = data[i];
            }

            if(length > 0)
                delete[] data;

            data = newData;
        }

        
        data[length++] = element;
    }


    void Print() const
    {
        for(int i = 0; i<length; i++)
        {
            std::cout<<data[i]<<"; ";
        }

        std::cout<<std::endl;
    }


    T operator[](unsigned int index) const
    {

        if(index >= length)
            throw "Out of array - DinArray";

        return data[index];
    }

    T& operator[](unsigned int index)
    {

        if(index >= length)
            throw "Out of array - DinArray";

        return data[index];
    }

    void operator=(const DinArray<T>& array)
    {
        capacity = array.capacity;
        threshold = array.threshold;
        length = array.length;

        if(length > 0)
            delete[] data;
            
        data = new T[capacity];
        

        for(int i = 0; i<array.length; i++)
        {
            data[i] = array.data[i];
        }
    }

    ~DinArray()
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr; // Mark as deleted
        }
    }
};

#endif