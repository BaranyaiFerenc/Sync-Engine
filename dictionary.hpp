#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>

template<typename ID, typename T>
class Dictionary
{
    struct DictionaryElement
    {
        ID id;
        T value;

        DictionaryElement* next;
    };

    DictionaryElement* first = 0;
    unsigned int size = 0;

public:

    Dictionary()
    {

    }

    DictionaryElement* GetEnd()
    {
        DictionaryElement* e;
        for(e = first; e->next != 0; e = e->next);

        return e;
    }

    void Add(ID identifier, T element)
    {
        DictionaryElement* newElement = new DictionaryElement();
        newElement->id = identifier; 
        newElement->value = element;
        newElement->next = 0;

        if(first == 0)
        {
            first = newElement;
        }
        else
        {
            GetEnd()->next = newElement;
        }
    }

    T operator[](ID id) const
    {
        for(DictionaryElement* e = first; e != 0; e = e->next)
        {
            if(e->id == id)
                return e->value;
        }

        return first->value;
    }
    
    T& operator[](ID id)
    {
        for(DictionaryElement* e = first; e != 0; e = e->next)
        {
            if(e->id == id)
                return e->value;
        }

        return first->value;
    }


    void Print() const
    {
        for(DictionaryElement* e = first; e != 0; e = e->next)
        {
            std::cout<<"["<<e->id<<" : "<<e->value<<"],";
        }
    }
};

#endif