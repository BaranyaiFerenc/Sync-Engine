#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "list.hpp"
#include <iostream>

template<int rows, int cols>
class Matrix
{
    double** data;

    double Multiplier(double* m1, double* m2)
    {
        double result = 0;
        for(int i = 0; i<cols; i++)
        {
            result+=m1[i]*m2[i];
        }

        return result;
    }

    double* GetColumn(unsigned int index)
    {
        double* col = new double[rows];
        for(int i = 0; i<rows; i++)
        {
            col[i] = data[i][index];
        }

        return col;
    }

public:

    Matrix()
    {
        data = new double*[rows];
        for(int r = 0; r < rows; r++)
        {
            data[r] = new double[cols];

            for(int c = 0; c<cols; c++)
            {
                data[r][c] = 0;
            }
        }
    }
/*
    Matrix(double** copy)
    {
        data = new T*[rows];
        for(int r = 0; r < rows; r++)
        {
            data[r] = new T[cols];

            for(int c = 0; c<cols; c++)
            {
                data[r][c] = copy[r][c];
            }
        }
    }
*/
    unsigned int ColumnCount() const {return cols;}
    unsigned int RowCount() const {return rows;}

    double* operator[](int index) const
    {
        return data[index];
    }

    
    double*& operator[](int index)
    {
        return data[index];
    }



    Matrix operator*(Matrix& mx)
    {
        Matrix<rows, mx.ColumnCount()> result;

        for(int r = 0; r < rows; r++)
        {
            for(int c = 0; c < mx.ColumnCount(); c++)
            {
                double* col = mx.GetColumn(c);
                result[r][c] = Multiplier(data[r], col);

                delete[] col;
            }
        }

        return result;
    }

    void Print() const
    {
        for(int r = 0; r < rows; r++)
        {
            for(int c = 0; c<cols; c++)
            {
                std::cout<<"["<<data[r][c]<<"]";
            }
            std::cout<<std::endl;
        }
    }



    ~Matrix()
    {
        for(int r = 0; r < rows; r++)
        {
            delete[] data[r];
        }
    }
};


#endif