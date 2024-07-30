#ifndef IMPORT_HPP
#define IMPORT_HPP


#include "object.hpp"
#include "dinarray.hpp"
#include "list.hpp"

#include <iostream>
#include <fstream>

namespace Import
{
    DinArray<Object> ImportObj(const char* path)
    {
        DinArray<Object> obj;

        std::fstream input(path);

        char array[256];
        int n = 256;

        Object actual;

        int vertexCounter = 0;
        int toRemove = 0;

        while(input.getline(array,n))
        {
            String line = array;

            if(line.Length() > 1 && line[0] == 'v' && line[1] == ' ')
            {
                List<String> list = line.Split(' ');

                char* x_char = list[1].toCharArray();
                char* y_char = list[2].toCharArray();
                char* z_char = list[3].toCharArray();

                actual.transform.mesh.vertices.Add(Vector(atof(x_char),atof(y_char),atof(z_char)));

                delete[] x_char;
                delete[] y_char;
                delete[] z_char;

                vertexCounter++;
            }
            else if(line.Length() > 1 && line[0] == 'f' && line[1] == ' ')
            {
                List<String> list = line.Split(' ');
                DinArray<int> faces(600);

                for(int i = 1; i<list.Size(); i++)
                {
                    char* num = list[i].Split('/')[0].GetText();
                    faces.Add(atoi(num)-1-toRemove);
                    delete[] num;
                }

                actual.transform.mesh.faces.Add(faces);
            }
            else if(line.Length() > 1 && line[0] == 'o' && line[1] == ' ')
            {
                if(actual.name == "")
                {
                    actual = Object();
                    actual.name = line.Split(' ')[1];
                }
                else
                {
                    actual.transform.CalculatePivot();
                    obj.Add(actual);
                    actual = Object();
                    actual.name = line.Split(' ')[1];
                    toRemove = vertexCounter;
                }
            }
        }

        input.close();
        actual.transform.CalculatePivot();
        obj.Add(actual);

        return obj;
    }
};

#endif