#pragma once

#include <cmath>

#include <iostream>

template <typename T = float>
class Matrix
{
public:
	typedef T valueType;
	typedef Matrix<T> Type;

private:
	unsigned rows, cols;

	T * data;

	void allocate(unsigned rows_, unsigned cols_)
	{
		free();

		if(rows_ == 0 || cols_ == 0)
			throw std::invalid_argument("Tried to allocate matrix of zero size.");

		data = new T[rows_ * cols_];

		if(!data)
			throw std::bad_alloc("Couldn't allocate memory for matrix.");

		rows = rows_;
		cols = cols_;
	}

	void free()
	{		
		if(data)
			delete [] data;

		data = NULL;
		rows = 0;
		cols = 0;
	}

public:
	Matrix()
	{	
		rows = 0;
		cols = 0;
		data = NULL;
	}

	template <typename vT>
	Matrix(const Matrix<vT> &v)
	{
		assign(v);
	}

	Matrix(unsigned rows_, unsigned cols_, const valueType& v)
	{
		rows = 0;
		cols = 0;
		data = NULL;

		allocate(rows_, cols_);
		assign(v);
	}

	//Matrix(unsigned rows, unsigned cols, const valueType* v)
	//{
	//	allocate(rows, cols)

	//	for(int i = 0; i < rows * cols; i++)
	//		data[i] = v[i];
	//}

	valueType& get(unsigned i, unsigned j)
	{
		if(i > rows || j > cols)
			throw std::invalid_argument("Matrix::get() argument out of range");

		return data[i * cols + j];
	}

	const valueType& get(unsigned i, unsigned j) const
	{
		if(i > rows || j > cols)
			throw std::invalid_argument("Matrix::get() argument out of range");

		return data[i * cols + j];
	}

	bool isValid() const { return data != NULL && rows != 0 && cols != 0; }
	unsigned countRows() const { return rows; }
	unsigned countCols() const { return cols; }

	template <typename vT>
	void assign(const Matrix<vT> &v)
	{
		allocate(v.countRows, v.countCols);
		
		for(unsigned i = 0; i < rows * cols; i++)
			data[i] = valueType(v.data[i]);
	}

	void assign(const valueType &v)
	{
		for(unsigned i = 0; i < rows * cols; i++)
			data[i] = v;
	}

	template <typename vT>
	void operator = (const Matrix<vT> &v)
	{
		assign(v);
	}

	template <typename vT>
	Type& operator += (const Matrix<vT> &v)
	{
		if(rows != v.rows || cols != v.cols)
			throw std::invalid_argument("Cannot add matrix of different size.");

		for(unsigned i = 0; i < rows * cols; i++)
			data[i] += valueType(v.data[i]);

		return *this;
	}

	template <typename vT>
	Type& operator -= (const Matrix<vT> &v)
	{
		if(rows != v.rows || cols != v.cols)
			throw std::invalid_argument("Cannot subtract matrix of different size.");

		for(int i = 0; i < rows * cols; i++)
			data[i] -= valueType(v.data[i]);

		return *this;
	}

	template <typename vT>
	Type& operator *= (const Matrix<vT> &v)
	{
		*this = *this * v;
		return *this;
	}

	Type& operator *= (const valueType& v)
	{
		for(int i = 0; i < rows * cols; i++)
			data[i] *= v;
	
		return *this;
	}

	Type& operator /= (const valueType& v)
	{
		for(int i = 0; i < rows * cols; i++)
			data[i] /= v;

		return *this;
	}

	template <typename vT>
	Type operator + (const Matrix<vT> &v) const
	{
		return Type(*this) += v;
	}

	template <typename vT>
	Type operator - (const Matrix<vT> &v) const
	{
		return Type(*this) -= v;
	}

	Type operator - () const
	{
		return Type(*this) *= -1;
	}

	template <typename vT>
	Type operator * (const Matrix<vT> &v) const
	{
		if(v.rows != cols)
			throw std::invalid_argument("Matrices not suitable for multiplication.");

		Matrix<T> result(rows, v.cols, 0);

		for(unsigned i = 0; i < rows; i++)
			for(unsigned j = 0; j < v.cols; j++)
			{
				for(unsigned k = 0; k < v.rows; k++)
					result.get(i, j) +=  get(i, k) * v.get(k, j);
			}

		return result;
	}

	Type operator * (const valueType& v) const
	{
		return Matrix<T, rows, cols>(*this) *= v;
	}

	Type operator / (const valueType& v) const
	{
		return Matrix<T, rows, cols>(*this) /= v;
	}

	valueType det(bool throwIfNotSquare = false) const
	{
		if (rows != cols)
		{
			if(throwIfNotSquare)
				throw std::invalid_argument("Need square matrix to calculate determinant.");
			else
				return valueType(0);
		}

		valueType d = 0;
		
		if (rows == 1)
		{
			// this is a 1 x 1 matrix
			d = data[0];
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 matrix
			// the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
			d = data[0] * data[3] - data[2] * data[1];
		}
		else
		{
			// this is a matrix of 3 x 3 or larger
			for (int c = 0; c < cols; c++)
			{
				Type M = minor(0, c);
				//d += pow(-1, 1+c)  * a.get(1, c) * Det(M);
				d += (c%2 + c%2 - 1) * get(0, c) * M.det();  // faster than with pow()
			}
		}

		return d;
	}

	
    Type minor(unsigned row, unsigned col) const
    {
        if (row <= rows && col <= cols)
        {
            Type res(rows - 1, cols - 1, 0);
 
            // copy the content of the matrix to the minor, except the selected
            for (int r = 0; r < rows - 1; r++)
                for (int c = 1; c < cols - 1; c++)
                {
                    res.get(r, c) = get(r + (r >= row), c + (c >= col));
                }

			return res;
        }
 
        return Type(*this);
    }

	Type transpose() const
	{
		Type res;

		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
					result.get(i, j) =  get(j, i);

		return res;
	}

	void print_oneline() const
	{
		std::cout << "{"
			
		for(int i = 0; i < rows; i++)
		{
			std::cout << "[";
			
			for(int j = 0; j < cols; j++)
			{
				std::cout << get(i, j);

				if(j != cols - 1)
					std::cout << ", ";

			}
			std::cout << "]";

			if(i != rows - 1)
				std::cout << ", ";
		}

		std::cout << "}";
	}

	void print_multiline() const
	{			
		for(int i = 0; i < rows; i++)
		{
			std::cout << "[";
			
			for(int j = 0; j < cols; j++)
			{
				std::cout << get(i, j);

				if(j != cols - 1)
					std::cout << ", ";

			}

			std::cout << "]" << std::endl;
		}
	}

};