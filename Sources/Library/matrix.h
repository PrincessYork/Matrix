#include <iostream>
#include <iomanip>
#include <typeinfo>
#include "stream_defines.h"
#include "functions_headers.h"
#include <math.h>

using namespace STD_NAMESPACE;

#ifndef MATRIX_H
#define MATRIX_H

template <class TypeOfMatrixElements>
class Matrix
{
public :

    Matrix();
    Matrix(string _name);
    Matrix(Matrix& copying_matrix);
    Matrix(string _name, int _rows, int _columns);

    ~Matrix();

    class MatrixArithmeticException
    {
    public :

        enum situation {culprit_x1, culprit_x2};
        enum errorflag {add, deduct, multiplication, division, equal, determinant, unknown};
        situation sit;
        errorflag flag;
        Matrix *culprit_1;
        Matrix *culprit_2;

        MatrixArithmeticException(Matrix *first_culprit, Matrix *second_culprit, situation s, errorflag f) : culprit_1(first_culprit), culprit_2(second_culprit), sit(s), flag(f)
        {}
        MatrixArithmeticException(Matrix *culprit, situation s, errorflag f) : culprit_1(culprit), culprit_2(nullptr), sit(s), flag(f)
        {}

        inline void print_message()
        {
            switch(sit)
            {
            case culprit_x1 : errormsg_one_culprit(); break;
            case culprit_x2 : errormsg_two_culprits(); break;
            }
        }

    private :

        inline void errormsg_two_culprits()
        {
            string what_happened;

            switch(flag)
            {
            case add : what_happened = " CAN'T ADD "; break;
            case deduct : what_happened = " CAN'T DEDUCT "; break;
            case multiplication : what_happened = " CAN'T MULTIPLICATE "; break;
            case division : what_happened = " CAN'T DIVISOR "; break;
            case equal : what_happened = " CAN'T EQUAL "; break;
            default : what_happened = " NON CONCRETIZE ERROR "; break;
            }

            STD_ERROR_STREAM << "\n#matrix error [arithmetic] : " << what_happened << "\"" << culprit_1->name << "\""
                             << "[" << culprit_1->rows << "][" << culprit_1->columns << "] and "
                             << "\"" << culprit_2->name << "\""
                             << "[" << culprit_2->rows << "][" << culprit_2->columns << "]\n";
        }

        inline void errormsg_one_culprit()
        {
            string what_happened;

            switch(flag)
            {
            case determinant : what_happened = " CAN'T GET DETERMINANT "; break;
            default : what_happened = " NON CONCRETIZE ERROR "; break;
            }

            STD_ERROR_STREAM << "\n#matrix error [arithmetic] : " << what_happened << "\"" << culprit_1->name << "\""
                             << "[" << culprit_1->rows << "][" << culprit_1->columns << "]\n";
        }
    };
    class MatrixAccessException
    {
    public :

        short place_1;
        short place_2;
        enum situation {row_col, row_row, col_col};
        situation sit;
        Matrix *culprit;

        MatrixAccessException(short first_place, short second_place, Matrix *culp, situation f) : place_1(first_place), place_2(second_place), culprit(culp), sit(f)
        {}

        inline void print_message()
        {
            switch(sit)
            {
            case row_col : STD_ERROR_STREAM << "\n#matrix error [access] : ATTEMPT TO GAIN ACCESS TO MATRIX \"" << culprit->name << "\" ROW : " << place_1 << " COLUMN : " << place_2 << endl; break;
            case row_row : STD_ERROR_STREAM << "\n#matrix error [access] : ATTEMPT TO GAIN ACCESS TO MATRIX \"" << culprit->name << "\" ROW : " << place_1 << " ROW : " << place_2 << endl; break;
            case col_col : STD_ERROR_STREAM << "\n#matrix error [access] : ATTEMPT TO GAIN ACCESS TO MATRIX \"" << culprit->name << "\" COLUMN : " << place_1 << " COLUMN : " << place_2 << endl; break;
            }
        }

    };
    class MatrixTypeException
    {
    public :
        string function_name;
        string type_name;

        MatrixTypeException(string _function_name, string _type_name) : function_name(_function_name)
        {
            if(_type_name == static_cast<string>(typeid(short).name()))
                type_name = "short";
            else if(_type_name == static_cast<string>(typeid(int).name()))
                type_name = "int";
            else if(_type_name == static_cast<string>(typeid(long).name()))
                type_name = "long";
            else if(_type_name == static_cast<string>(typeid(float).name()))
                type_name = "float";
            else if(_type_name == static_cast<string>(typeid(double).name()))
                type_name = "double";
            else if(_type_name == static_cast<string>(typeid(long double).name()))
                type_name = "long double";
            else if(_type_name == static_cast<string>(typeid(char).name()))
                type_name = "char";
            else if(_type_name == static_cast<string>(typeid(string).name()))
                type_name = "string";
            else
                type_name = "unknown";
        }

        inline void print_message()
        {
            STD_ERROR_STREAM << "\n#matrix error [type] : TRYING TO CALL \"" << function_name << "\" FUNCTION "
                             << "WITH TYPE \"" << type_name << "\"\n";
        }
    };

    void show();
    void setElements();
    void resestIfNotEmpty();

    bool hasSameRows();
    bool hasSameColumns();
    bool hasNullRows();
    bool hasNullColumns();
    bool operator == (const Matrix& comparable_matrix);

    short getRank();
    short howManyNullRows();

    TypeOfMatrixElements getCompliment(short row, short column);
    TypeOfMatrixElements getDeterminant();
    TypeOfMatrixElements& editElement(short row, short column);
    TypeOfMatrixElements& at(short row, short column);

    Matrix getMinor(short row, short column);
    Matrix getAdjoint();
    Matrix getReverse();
    Matrix multiplicate(Matrix& multiplier_matrix);

    Matrix operator + (Matrix& addable_matrix);
    Matrix operator - (Matrix& deductible_matrix);
    Matrix operator * (Matrix& multiplier_matrix);
    Matrix operator / (Matrix& divisor_matrix);
    Matrix operator % (Matrix& divisor_matrix);

    Matrix& transpose();
    Matrix& stairStep();
    Matrix& swapRows(short row_a, short row_b);
    Matrix& swapColumns(short column_a, short column_b);
    Matrix& fill(TypeOfMatrixElements fill_element);
    Matrix& resize(short new_rows, short new_columns);

    Matrix& operator = (const Matrix& equalable_matrix);
    Matrix& operator += (const Matrix& addable_matrix);
    Matrix& operator += (const TypeOfMatrixElements& addable_element);
    Matrix& operator -= (const Matrix& deductible_matrix);
    Matrix& operator -= (const TypeOfMatrixElements& deductible_element);
    Matrix& operator *= (const Matrix& multiplier_matrix);
    Matrix& operator *= (const TypeOfMatrixElements& multiplier_element);
    Matrix& operator /= (const Matrix& divisor_matrix);
    Matrix& operator /= (const TypeOfMatrixElements& divisor_element);
    Matrix& operator %= (const Matrix& divisor_matrix);
    Matrix& operator %= (const TypeOfMatrixElements& divisor_element);

    template <class Type>
    friend Matrix<Type> operator + (const Matrix<Type>& base_matrix, const Type& addable_element);

    template <class Type>
    friend Matrix<Type> operator + (const Type& addable_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator - (const Matrix<Type>& base_matrix, const Type& deductible_element);

    template <class Type>
    friend Matrix<Type> operator - (const Type& deductible_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator * (const Matrix<Type>& base_matrix, const Type& multiplier_element);

    template <class Type>
    friend Matrix<Type> operator * (const Type& multiplier_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator / (const Matrix<Type>& base_matrix, const Type& divisor_element);

    template <class Type>
    friend Matrix<Type> operator / (const Type& divisor_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator % (const Matrix<Type>& base_matrix, const Type& divisor_element);

    template <class Type>
    friend Matrix<Type> operator % (const Type& divisor_element, const Matrix<Type>& base_matrix);

private :

    string name;
    short rows;
    short columns;

    TypeOfMatrixElements **elements;

    short getMinimumRow();
    short getMaximumRow();
    short getLongestElementLength();
};

//constructors & destructors

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix()
{
    rows = 0;
    columns = 0;
    name = "EMPTY";
    elements = nullptr;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(string _name)
{
    rows = 0;
    columns = 0;
    name = _name;
    elements = nullptr;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(Matrix<TypeOfMatrixElements>& copying_matrix)
{
      int i, j;

    resestIfNotEmpty();

    try
    {
        rows = copying_matrix.rows;
        columns = copying_matrix.columns;

        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = copying_matrix.elements[i][j];
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(string _name, int _rows, int _columns) : name(_name), rows(_rows), columns(_columns)
{
      int i, j;

    try
    {
        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = static_cast<TypeOfMatrixElements>(0);
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::~Matrix()
{
      int i;

    for(i = 0; i < rows; ++i)
        delete [] elements[i];

    delete [] elements;
}

//constructors & destructors END

//functions

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::getLongestElementLength()
{
    short longest_element_size = 2;
    bool sign = false;
    bool integer = true;

      int i, j;

    if(
            typeid(TypeOfMatrixElements) == typeid(long double) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(float)
      )
        integer = false;

    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
        {
            short current_element_size = 1;
            TypeOfMatrixElements current_element;
            int current_integer_element;

            if(integer)
            {
                current_element = elements[i][j];

                while(current_element /= 10)
                    ++current_element_size;

                sign = (current_element < 0) ? true : sign;
            }
            else
            {
                current_integer_element = elements[i][j];

                while(current_integer_element /= 10)
                    ++current_element_size;

                sign = (current_integer_element < 0) ? true : sign;
            }

            longest_element_size = (current_element_size > longest_element_size) ? current_element_size : longest_element_size;
        }

    longest_element_size += (sign) ? 1 : 0;
    longest_element_size += (integer) ? 0 : 2;

    return longest_element_size + 2;
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::show()
{
    STD_OUT_STREAM << "\n\nMatrix \"" << name << "\" [" << rows << "][" << columns << "] : ";
    STD_OUT_STREAM << setiosflags(ios::right);

    if(
            typeid(TypeOfMatrixElements) == typeid(long double) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(float)
      )
        STD_OUT_STREAM << setiosflags(ios::fixed) << setprecision(1);

      int i, j;
    short printable_size = this->getLongestElementLength();

    for(i = 0; i < rows; ++i)
    {
        STD_OUT_STREAM << endl;
        STD_OUT_STREAM << " |";
        for(j = 0; j < columns; ++j)
            STD_OUT_STREAM << setw(printable_size) << elements[i][j];
        STD_OUT_STREAM << setw(2) << setiosflags(ios::right) << " | ";
    }
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::setElements()
{
      int i, j;

    STD_OUT_STREAM << "\nMatrix \"" << name << "\" [" << rows << "][" << columns << "] elements setup : \n";
    STD_INPUT_STREAM.unsetf(ios::skipws);
    STD_OUT_STREAM << endl << "+" << setw(35) << setfill('-') << "+" << setfill(' ') << endl;

    for(i = 0; i < rows; ++i)
    {
        for(j = 0; j < columns; ++j)
        {
            for(;;)
            {
                STD_OUT_STREAM << "| " << setw(10) << name << "[" << i + 1 << "][" << j + 1 << "] : ";
                STD_INPUT_STREAM >> elements[i][j];
                if(STD_INPUT_STREAM.good())
                {
                    STD_INPUT_STREAM.ignore(10, '\n');
                    break;
                }
                else
                {
                    STD_INPUT_STREAM.clear();
                    STD_INPUT_STREAM.ignore(10, '\n');
                    STD_OUT_STREAM << "| #error [input] : INCORRECT INPUT" << endl;
                }
            }
        }
        STD_OUT_STREAM << "+" << setw(35) << setfill('-') << setiosflags(ios::right) << "+" << setfill(' ') << endl;
    }

    STD_INPUT_STREAM.setf(ios::skipws);
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::transpose()
{
      int i, j;
    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
            swap(elements[i][j], elements[j][i]);

    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::stairStep()
{
      int i, j, k;

    if(elements[0][0] == 0)
        swapRows(1, getMaximumRow());

    k = 0;

    while(k < rows)
    {
        TypeOfMatrixElements coefficient_1 = elements[k][k];
        for(i = k + 1; i < rows; ++i)
        {
            TypeOfMatrixElements coefficient_2 = elements[i][k];
            for(j = k; j < columns; ++j)
            {
                elements[i][j] *= coefficient_1;
                elements[i][j] -= elements[k][j] * coefficient_2;
            }
        }
        ++k;
    }

    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::swapRows(short row_a, short row_b)
{
    --row_a;
    --row_b;

    if(row_a < rows && row_b < rows && row_a >= 0 && row_b >= 0)
    {
        swap(elements[row_a], elements[row_b]);
        return *this;
    }
    else
    {
        throw MatrixAccessException(row_a + 1, row_b + 1, this, MatrixAccessException::row_row);
    }

}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::swapColumns(short column_a, short column_b)
{
      int i, j;

    --column_a;
    --column_b;

    if(column_a < columns && column_b < columns && column_a >= 0 && column_b >= 0)
    {
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                if(j == column_a)
                    swap(elements[i][j], elements[i][column_b]);
        return *this;
    }
    else
    {
        throw MatrixAccessException(column_a + 1, column_b + 1, this, MatrixAccessException::col_col);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::fill(TypeOfMatrixElements fill_element)
{
      int i, j;
    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
            elements[i][j] = fill_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::resize(short new_rows, short new_columns)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", new_rows, new_columns);
      int i, j;

    if(new_rows > 0 && new_columns > 0)
    {
        if(rows < new_rows && columns < new_columns)
        {
            for(i = 0; i < rows; ++i)
                for(j = 0; j < columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows > new_rows && columns > new_columns)
        {
            for(i = 0; i < new_rows; ++i)
                for(j = 0; j < new_columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows >= new_rows && columns <= new_columns)
        {
            for(i = 0; i < new_rows; ++i)
                for(j = 0; j < columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows <= new_rows && columns >= new_columns)
        {
            for(i = 0; i < rows; ++i)
                for(j = 0; j < new_columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }

        *this = temp;
        return *this;
    }
    else
    {
        throw MatrixAccessException(new_rows, new_columns, this, MatrixAccessException::row_col);
    }
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::resestIfNotEmpty()
{
    if(rows != 0 && columns != 0 && elements != nullptr)
    {
          int i;
        for(i = 0; i < rows; ++i)
            delete [] elements[i];
        delete [] elements;
        rows = columns = 0;
    }
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements Matrix<TypeOfMatrixElements>::getCompliment(short row, short column)
{
    return pow(-1, row + column) * getMinor(row, column).getDeterminant();
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements Matrix<TypeOfMatrixElements>::getDeterminant()
{
     if(rows != columns)
         throw MatrixArithmeticException(this, MatrixArithmeticException::culprit_x1, MatrixArithmeticException::determinant);

     if(rows >= 4 && columns >= 4)
     {
         if(hasSameRows() || hasSameColumns() || hasNullRows() || hasNullColumns())
             return 0;

         TypeOfMatrixElements determinant = 0;

         for(int j = 0; j < columns; ++j)
             determinant += elements[0][j] * pow(-1, 1 + j + 1) * getMinor(1, j + 1).getDeterminant();
         return determinant;
     }
     else if(rows == 3 && columns == 3)
     {
         TypeOfMatrixElements determinant;

         determinant = elements[0][0] * elements[1][1] * elements[2][2] +
                 elements[1][0] * elements[2][1] * elements[0][2] +
                 elements[0][1] * elements[1][2] * elements[2][0] -
                 elements[0][2] * elements[1][1] * elements[2][0] -
                 elements[1][2] * elements[2][1] * elements[0][0] -
                 elements[0][1] * elements[1][0] * elements[2][2];

         return determinant;
     }
     else if(rows == 2 && columns == 2)
         return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
     else
         return elements[0][0];
}

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::getRank()
{
    Matrix<TypeOfMatrixElements> temp("TEMP");
    temp = *this;
    temp.stairStep();

    return temp.rows - temp.howManyNullRows();
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::getReverse()
{
    if(
            typeid(TypeOfMatrixElements) == typeid(float) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(long double)
      )
    {
        Matrix<TypeOfMatrixElements> reverse_matrix("REVERSE", rows, columns);
        reverse_matrix = getAdjoint() / getDeterminant();
        return reverse_matrix;
    }
    else
    {
        throw MatrixTypeException("getReverse()", typeid(TypeOfMatrixElements).name());
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::multiplicate(Matrix<TypeOfMatrixElements>& multiplier_matrix)
{
    if(columns == multiplier_matrix.rows)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, multiplier_matrix.columns);
          int i, j, k;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < multiplier_matrix.columns; ++j)
            {
                TypeOfMatrixElements sum = 0;
                for(k = 0; k < columns; ++k)
                    sum += elements[i][k] * multiplier_matrix.elements[k][j];
                temp.elements[i][j] = sum;
            }
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &multiplier_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::multiplication);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::getAdjoint()
{
    Matrix<TypeOfMatrixElements> adjoint_matrix("ADJOINT", rows, columns);
      int i, j;
    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
            adjoint_matrix.editElement(i + 1, j + 1) = getCompliment(j + 1, i + 1);
    return adjoint_matrix;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::getMinor(short excluded_row, short excluded_column)
{
    Matrix<TypeOfMatrixElements> minor_matrix("MINOR", rows - 1, columns - 1);
      int i = 0, j = 0, minor_row = 0, minor_column = 0;

    --excluded_row;
    --excluded_column;

    if(excluded_row < rows && excluded_column < columns && excluded_row >= 0 && excluded_column >= 0 && rows == columns)
    {
        for(i = 0; i < rows; ++i)
            if(i != excluded_row)
                for(j = 0; j < columns; ++j)
                    if(j != excluded_column)
                    {
                        minor_matrix.elements[minor_row][minor_column] = elements[i][j];
                        if(minor_column + 1 == minor_matrix.columns)
                        {
                            ++minor_row;
                            minor_column = 0;
                        }
                        else
                            ++minor_column;
                    }
        return minor_matrix;
    }
    else
    {
        throw MatrixAccessException(excluded_row + 1, excluded_column + 1, this, MatrixAccessException::row_col);
    }
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements& Matrix<TypeOfMatrixElements>::editElement(short row, short column)
{
    if(row <= rows && row > 0 && column <= columns && column > 0)
    {
        return elements[row - 1][column - 1];
    }
    else
    {
        throw MatrixAccessException(row, column, this, MatrixAccessException::row_col);
    }
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements& Matrix<TypeOfMatrixElements>::at(short row, short column)
{
    if(row <= rows && row > 0 && column <= columns && column > 0)
    {
        return elements[row - 1][column - 1];
    }
    else
    {
        throw MatrixAccessException(row, column, this, MatrixAccessException::row_col);
    }
}

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::getMinimumRow()
{
      int i, j;
    short min_row = 0;

    for(i = min_row + 1; i < rows; ++i)
        for(j = 0; j < columns; ++j)
        {
            if(elements[min_row][j] == 0 && elements[i][j] != 0)
                min_row = i;
            else if(elements[i][j] > elements[min_row][j])
                break;
            else if(elements[i][j] < elements[min_row][j] && elements[i][j] != 0)
                min_row = i;
        }

    return min_row + 1;
}

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::getMaximumRow()
{
      int i, j;
    short max_row = 0;

    for(j = 0; j < columns; ++j)
        for(i = 0; i < rows; ++i)
            if(elements[max_row][j] < elements[i][j])
            {
                max_row = i;
                return max_row + 1;
            }
    return max_row + 1;
}

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::howManyNullRows()
{
      int i, j;
    bool is_null = true;
    short null_rows = 0;

    for(i = 0; i < rows; ++i)
    {
        is_null = true;

        for(j = 0; j < columns; ++j)
            is_null *= (elements[i][j] == 0) ? true : false;
        if(is_null)
            ++null_rows;
    }

    return null_rows;
}

//functions/bool

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::hasSameRows()
{
      int i, j, k;
    bool find_same = true;

    for(i = 0, find_same = true; i < rows; ++i)
        for(j = i + 1, find_same = true; j < rows; ++j)
        {
            for(k = 0; k < columns; ++k)
                find_same *= (elements[i][k] == elements[j][k]) ? true : false;
            if(find_same)
                return true;
        }

    return false;
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::hasSameColumns()
{
      int i, j, k;
    bool find_same = true;

    for(i = 0, find_same = true; i < columns; ++i)
        for(j = i + 1, find_same = true; j < columns; ++j)
        {
            for(k = 0; k < rows; ++k)
                find_same *= (elements[k][i] == elements[k][j]) ? true : false;
            if(find_same)
                return true;
        }

    return false;
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::hasNullRows()
{
      int i, j;
    bool is_null;

    for(i = 0, is_null = true; i < rows; ++i)
    {
        for(j = 0; j < columns; ++j)
            is_null *= (elements[i][j] == 0) ? true : false;
        if(is_null)
            return is_null;
    }

    return false;
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::hasNullColumns()
{
      int i, j;
    bool is_null;

    for(i = 0, is_null = true; i < columns; ++i)
    {
        for(j = 0; j < rows; ++j)
            is_null *= (elements[j][i] == 0) ? true : false;
        if(is_null)
            return is_null;
    }

    return false;
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::operator == (const Matrix<TypeOfMatrixElements>& comparable_matrix)
{
    if(
            typeid(TypeOfMatrixElements) == typeid(float) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(long double)
      )
    {
        throw MatrixTypeException("operator == ", typeid(TypeOfMatrixElements).name());
    }
    else
    {
        if(rows == comparable_matrix.rows && columns == comparable_matrix.columns)
        {
            bool iscompare = true;
              int i, j;
            for(i = 0; i < rows; ++i)
                for(j = 0; j < columns; ++j)
                    iscompare = (elements[i][j] == comparable_matrix.elements[i][j]) ? iscompare : false;
            return iscompare;
        }
        else
        {
            return false;
        }
    }
}

//functions/bool END

//functios END

//operators/arithmetic

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator + (Matrix<TypeOfMatrixElements>& addable_matrix)
{
    if(rows == addable_matrix.rows && columns == addable_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
          int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] + addable_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &addable_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::add);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator - (Matrix<TypeOfMatrixElements>& deductible_matrix)
{
    if(rows == deductible_matrix.rows && columns == deductible_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
          int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] - deductible_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &deductible_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::deduct);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator * (Matrix<TypeOfMatrixElements>& multiplier_matrix)
{
    if(rows == multiplier_matrix.rows && columns == multiplier_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
          int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] * multiplier_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &multiplier_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::multiplication);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator / (Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    if(rows == divisor_matrix.rows && columns == divisor_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
          int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] / divisor_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &divisor_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::division);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator % (Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    if(rows == divisor_matrix.rows && columns == divisor_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
          int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] % divisor_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException(this, &divisor_matrix, MatrixArithmeticException::culprit_x2, MatrixArithmeticException::division);
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator = (const Matrix<TypeOfMatrixElements>& equalable_matrix)
{
      int i, j;

    resestIfNotEmpty();

    try
    {
        rows = equalable_matrix.rows;
        columns = equalable_matrix.columns;

        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = equalable_matrix.elements[i][j];
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator += (const Matrix& addable_matrix)
{
    *this = *this + addable_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator += (const TypeOfMatrixElements& addable_element)
{
    *this = *this + addable_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator -= (const Matrix& deductible_matrix)
{
    *this = *this - deductible_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator -= (const TypeOfMatrixElements& deductible_element)
{
    *this = *this - deductible_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator *= (const Matrix& multiplier_matrix)
{
    *this = *this * multiplier_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator *= (const TypeOfMatrixElements& multiplier_element)
{
    *this = *this * multiplier_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator /= (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    *this = *this / divisor_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator /= (const TypeOfMatrixElements& divisor_element)
{
    *this = *this / divisor_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator %= (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    *this = *this % divisor_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator %= (const TypeOfMatrixElements& divisor_element)
{
    *this = *this % divisor_element;
    return *this;
}

//operators/arithmetic/friend

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator + (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& addable_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] + addable_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator + (const TypeOfMatrixElements& addable_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] + addable_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator - (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& deductible_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] - deductible_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator - (const TypeOfMatrixElements& deductible_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = deductible_element - base_matrix.elements[i][j];
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator * (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& multiplier_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] * multiplier_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator * (const TypeOfMatrixElements& multiplier_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] * multiplier_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator / (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& divisor_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] / divisor_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator / (const TypeOfMatrixElements& divisor_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = divisor_element / base_matrix.elements[i][j];
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator % (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& divisor_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] % divisor_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator % (const TypeOfMatrixElements& divisor_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
      int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = divisor_element % base_matrix.elements[i][j];
    return temp;
}

//operators/arithmetic/friend END

//operatorsarithmetic/ END

#endif // MATRIX_H
