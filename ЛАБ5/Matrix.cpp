#include "stdafx.h"
#include "Matrix.h"
using namespace std;
using namespace Math;

int Matrix::count = 0;

Matrix::Matrix() :Matrix::Matrix(0, 0, NULL) {}

Matrix::Matrix(int _row, const double* arr) : Matrix::Matrix(_row, _row, arr) {}

Matrix::Matrix(int _row, int _col, const double* arr)
{
	count++;
	id = count;
	if (_row < 0 || _col < 0) 
		throw("Количетсво строк или столбцов < 0 в матрице: " + to_string(id));
	row = _row;
	col = _col;
	matrix = row * col ? new double[row * col] : NULL;
	if (arr != NULL)
	{
		for (int i = 0; i < row * col; i++)
			matrix[i] = arr[i];
	}
	else
		for (int i = 0; i < row * col; i++)
			matrix[i] = 0;
}

Matrix::Matrix(const Matrix& obj2) :Matrix::Matrix(obj2.row, obj2.col, obj2.matrix)
{
}

Matrix::Matrix(Matrix&& obj2) : Matrix::Matrix()
{
	operator=(obj2);
}

Matrix::~Matrix()
{
	row = 0;
	col = 0;
	if (matrix != 0)
		delete[]matrix;
}

int Matrix::GetRow() const
{
	return row;
}

int Matrix::GetCol() const
{
	return col;
}

int Matrix::GetId() const
{
	return id;
}

int Matrix::GetCount()
{
	return count;
}

double Matrix::Index::operator[] (int index) const  
{
	if (index < 0 || index >= col)
	{
		throw "Неверный индекс [][!] " + std::to_string(id);
	}
	return arr[index];
}
double& Matrix::Index::operator[] (int index)  
{
	if (index < 0 || index >= col)
	{
		throw "Неверный индекс [][!]" + std::to_string(id);
	}
	return arr[index];
}


const Matrix::Index Matrix::operator [] (int index) const 
{
	if (index < 0 || index >= row)
	{
		throw "Неверный индекс [!][]" + std::to_string(id);
	}
	Index arrind(matrix + index * col, col, id);

	return arrind;
}

Matrix::Index Matrix::operator [] (int index) 
{
	if (index < 0 || index >= row)
	{
		throw "Неверный индекс [!][]" + std::to_string(id);
	}
	Index arrind(matrix + index * col, col, id);

	return arrind;
}

Matrix::Index::Index(double* p, int colval, int _id) :arr(p), col(colval), id(_id) {}

Matrix::Index::~Index()
{
	arr = NULL;
}

double Matrix::FindMax() const
{
	if (matrix == 0) 
		throw ("Попытка найти минимальный элемент в матрице " + to_string(id)+ " с нулевым размером!");
	double max = matrix[0];
	for (int i = 1; i < row * col; i++)
	{
		if (matrix[i] > max)
			max = matrix[i];
	}
	return max;
}

double Matrix::FindMin() const
{
	if (matrix == 0) 
		throw ("Попытка найти минимальный элемент в матрице " + to_string(id) + " с нулевым размером");
	double min = matrix[0];
	for (int i = 1; i < row * col; i++)
	{
		if (matrix[i] < min)
			min = matrix[i];
	}
	return min;
}

int Matrix::GetSize() const
{
	return row * col;
}

bool Matrix::CheckMul(const Matrix& m2) const
{
	return col == m2.row;
}
bool Matrix::CheckSum(const Matrix& m2) const
{
	return ((row == m2.row) && (col == m2.col));
}

Matrix& Matrix::operator=(const Matrix& Matrix2)
{
	if (this != &Matrix2)
	{
		if (row*col != Matrix2.row * Matrix2.col)
		{
			if (matrix)
			{
				delete[] matrix;
				matrix = nullptr;
			}
			if (Matrix2.row * Matrix2.col > 0)
				matrix = new double[Matrix2.row * Matrix2.col];
		}
		row = Matrix2.row;
		col = Matrix2.col;
		for (int i = 0; i < row * col; i++)
		{
			matrix[i] = Matrix2.matrix[i];
		}
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& Matrix2)
{
	if (this != &Matrix2)
	{
		swap(matrix, Matrix2.matrix);
		swap(row, Matrix2.row);
		swap(col, Matrix2.col);
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& Matrix2)
{
	bool check = CheckSum(Matrix2);
	if (!check) 
		throw ("Ошибка! Сумму или разность найти не возможно, количество строк или столбцов матриц: " + to_string(id) + " " + to_string(Matrix2.id) + " не совпадают");
	for (int i = 0; i < row * col; i++)
	{
		matrix[i] += Matrix2.matrix[i];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& Matrix2)
{
	bool check = CheckSum(Matrix2);
	if (!check) 
		throw ("Ошибка! Сумму или разность найти не возможно, количество строк или столбцов матриц: " + to_string(id) + " " + to_string(Matrix2.id) + " не совпадают");
	for (int i = 0; i < row * col; i++)
	{
		matrix[i] -= Matrix2.matrix[i];
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& Matrix2)
{
	bool check = CheckMul(Matrix2);
	if (!check) 
		throw ( "Ошибка! Произведение найти не возможно, количество строк матрицы " + to_string(id) + " не совпадает с количеством столбцов матрицы " + to_string(Matrix2.id));
	Matrix Matrix3(row, Matrix2.col);
	for (int i = 0; i < Matrix3.row; i++)
	{
		for (int j = 0; j < Matrix3.col; j++)
		{
			for (int k = 0; k < col; k++)
				Matrix3.matrix[i * Matrix3.col + j] += (matrix[i * col + k] * Matrix2.matrix[k * Matrix2.col + j]);
		}
	}
	*this = move(Matrix3);
	return *this;
}

Matrix& Matrix::operator*=(double k)
{
	for (int i = 0; i < row * col; i++)
	{
		matrix[i] *= k;
	}
	return *this;
}

Matrix Math::operator+(const Matrix& m1, const Matrix& m2)
{
	return Matrix(m1) += m2;
}

Matrix Math::operator-(const Matrix& m1, const Matrix& m2)
{
	return Matrix(m1) += m2;
}

Matrix Math::operator*(const Matrix& m1, const Matrix& m2)
{
	return Matrix(m1) *= m2;
}


Matrix Math::operator*(const Matrix& m1, double k)
{
	return Matrix(m1) *= k;
}

Matrix Math::operator*(double k, const Matrix& m1)
{
	return operator*(m1, k);
}

bool Math::operator == (const Matrix& obj1, const Matrix& obj2)
{
	if (obj1.GetSize() != obj2.GetSize())
		return false;
	for (int i = 0; i < obj1.GetSize(); i++)
		if (obj1.matrix[i] != obj2.matrix[i]) 
			return false;
	return true;
}

bool Math::operator != (const Matrix& obj1, const Matrix& obj2)
{
	if (obj1.GetSize() != obj2.GetSize())
		return true;
	for (int i = 0; i < obj1.GetSize(); i++)
		if (obj1.matrix[i] == obj2.matrix[i])
			return false;
	return true;
}

bool Math::operator >= (const Matrix& obj1, const Matrix& obj2)
{
	return obj1.GetSize() >= obj2.GetSize();
}

bool Math::operator <= (const Matrix& obj1, const Matrix& obj2)
{
	return obj1.GetSize() <= obj2.GetSize();
}

bool Math::operator > (const Matrix& obj1, const Matrix& obj2)
{
	return obj1.GetSize() > obj2.GetSize();
}

bool Math::operator < (const Matrix& obj1, const Matrix& obj2)
{
	return obj1.GetSize() < obj2.GetSize();
}

ostream& Math::operator<<(ostream& output, const Matrix& m)
{
	streamsize width = output.width();
	for (int i = 0; i < m.row; ++i)
	{
		for (int j = 0; j < m.col; ++j)
		{
			output << setw(width) << m[i][j];
			if (width == 0)
			{
				output << '\t';
			}
		}
		output << endl;
	}
	return output;
}