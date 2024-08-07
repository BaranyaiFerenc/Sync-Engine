#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "list.hpp"
#include <iostream>

class Matrix
{
    double** data;

    int rows, cols;

    double Multiplier(double* m1, double* m2) const 
    {
        double result = 0;
        for(int i = 0; i<cols; i++)
        {
            result+=m1[i]*m2[i];
        }

        return result;
    }

    double* GetColumn(unsigned int index) const 
    {
        double* col = new double[rows];
        for(int i = 0; i<rows; i++)
        {
            col[i] = data[i][index];
        }

        return col;
    }

public:

    Matrix(int rows_, int cols_)
    {
        rows = rows_;
        cols = cols_;

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

    Matrix(const Matrix& mx)
    {
        rows = mx.RowCount();
        cols = mx.ColumnCount();

        data = new double*[rows];
        for(int r = 0; r < rows; r++)
        {
            data[r] = new double[cols];

            for(int c = 0; c<cols; c++)
            {
                data[r][c] = mx[r][c];
            }
        }
    }

    void operator=(Matrix mx)
    {
        for(int r = 0; r < rows; r++)
        {
            delete[] data[r];
        }

        rows = mx.RowCount();
        cols = mx.ColumnCount();

        data = new double*[rows];
        for(int r = 0; r < rows; r++)
        {
            data[r] = new double[cols];

            for(int c = 0; c<cols; c++)
            {
                data[r][c] = mx[r][c];
            }
        }
    }

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


    void SetDiagonal(double value = 1)
    {
        for(int x = 0; x<RowCount(); x++)
        {
            data[x][x] = value;
        }
    }

    Matrix operator*(const Matrix mx) const
    {
        Matrix result(rows, mx.ColumnCount());

        for(unsigned int r = 0; r < rows; r++)
        {
            for(unsigned int c = 0; c < mx.ColumnCount(); c++)
            {
                double* col = mx.GetColumn(c);
                result[r][c] = Multiplier(data[r], col);

                delete[] col;
            }
        }

        return result;
    }

    void Print(bool indent = false) const
    {
        for(int r = 0; r < rows; r++)
        {
            if(indent)
                std::cout<<"\t";

            for(int c = 0; c<cols; c++)
            {
                std::cout<<"["<<data[r][c]<<"]";
            }
            std::cout<<std::endl;
        }
    }

    void PrintMultiplication(const Matrix& mx) const
    {
        Matrix result = *this*mx;

        mx.Print(true);
        std::cout<<std::endl;

        for(unsigned int i = 0; i<rows; i++)
        {
            for(unsigned int k = 0; k<cols; k++)
            {
                std::cout<<"["<<data[i][k]<<"]";
            }

            std::cout<<"  ";
            
            for(unsigned int k = 0; k<result.ColumnCount(); k++)
            {
                std::cout<<"["<<result[i][k]<<"]";
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