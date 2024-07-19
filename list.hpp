#include <iostream>

template<typename T>
class List
{
    struct Element
    {
        T value;

        Element* before = 0;
        Element* after = 0;
    };


    Element* firstElement = 0;
    unsigned int size = 0;

public:

    void Add(T element)
    {
        size++;

        if(firstElement == 0)
        {
            firstElement = new Element();
            firstElement->value = element;
            return;
        }


        Element* newElement = new Element();
        newElement->value = element;

        Element* lastElement = End();

        newElement->before = lastElement;
        lastElement->after = newElement;
    }

    void RemoveAt(unsigned int index)
    {
        if(size <= index)
            throw "Out of size";

        unsigned i = 0;

        for(Element* e = firstElement;  e != 0; e = e->after)
        {
            if(index == i++)
            {
                e->before->after = e->after;
                e->after->before = e->before;

                delete e;
            }
        }

        size--;

    }

    void Remove(T element, bool all = false)
    {
        for(Element* e = firstElement;  e != 0; e = e->after)
        {
            if(element == e->value)
            {
                e->before->after = e->after;
                e->after->before = e->before;

                delete e;

                if(!all)
                    return;
            }
        }
    }


    void Sort()
    {
        
    }

    Element* End()
    {
        Element* e = firstElement;
        for(e; e->after != 0; e = e->after);
        return e;
    }

    unsigned int Size() const {return size;}

    void Print() const
    {
        for(Element* e = firstElement; e != 0; e = e->after)
        {
            std::cout<<"["<<(e->value)<<"],";
        }

        std::cout<<std::endl;
    }


    T operator[](unsigned int index) const
    {
        if(size <= index)
            throw "Out of size";

        unsigned i = 0;

        for(Element* e = firstElement;  e != 0; e = e->after)
        {
            if(index == i++)
                return e->value;
        }

        throw "Element not found";
    }

    T& operator[](unsigned int index)
    {
        if(size <= index)
            throw "Out of size";

        unsigned i = 0;
        for(Element* e = firstElement;  e != 0; e = e->after)
        {
            if(index == i++)
                return e->value;
        }

        throw "Element not found";
    }

    

};