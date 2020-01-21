#pragma once
#include "stdafx.h"

using namespace std;

namespace Math
{
	template<typename T>
	class templateMatrix;

	template <typename T>
	typename ostream& operator<<(ostream& output, const templateMatrix<T>& m)
	{
		streamsize width = output.width();
		for (int i = 0; i < m.row; i++)
		{
			for (int j = 0; j < m.col; j++)
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

	template<typename T>
	templateMatrix<T> operator+(const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return templateMatrix<T>(m1) += m2;
	}
	template<typename T>
	templateMatrix<T> operator-(const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return templateMatrix<T>(m1) -= m2;
	}
	template<typename T>
	templateMatrix<T> operator*(const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return templateMatrix<T>(m1) *= m2;
	}

	template<typename T>
	typename templateMatrix<T> operator*(const templateMatrix<T>& m1, const T& k)
	{
		return templateMatrix<T>(m1) *= k;
	}
	template<typename T>
	typename templateMatrix<T> operator*(const T& k, const templateMatrix<T>& m1)
	{
		return operator*(m1, k);
	}

	template<typename T>
	bool operator == (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		if (m1.GetSize() != m2.GetSize())
			return false;
		for (int i = 0; i < m1.GetSize(); i++)
			if (m1.matrix[i] != m2.matrix[i]) 
				return false;
		return true;
	}
	template<typename T>
	bool operator != (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		if (m1.GetSize() != m2.GetSize())
			return true;
		for (int i = 0; i < m1.GetSize(); i++)
			if (m1.matrix[i] == m2.matrix[i]) 
				return false;
		return true;
	}
	template<typename T>
	bool operator >= (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return m1.GetSize() >= m2.GetSize();
	}


	template<typename T>
	bool operator <= (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return m1.GetSize() <= m2.GetSize();
	}

	template<typename T>
	bool operator > (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return m1.GetSize() > m2.GetSize();
	}



	template<typename T>
	class templateMatrix
	{
	private:
		T* matrix;
		int row;
		int col;

		int id;
		static int count;
		class Index
		{
		private:
			T *arr;
			int col;
			int id;
		public:
			Index(T * arr, int i, int _id);
			~Index();
			T& operator[](int j);
			const T& operator[](int j) const;
		};
	public:
		Index operator[](int i);
		const Index operator[](int i) const;
		templateMatrix();
		templateMatrix(int _row , int _col, const T* mtrx=NULL);
		templateMatrix(int _row , const T* mtrx=NULL);
		templateMatrix(const templateMatrix<T>& obj2);
		templateMatrix(templateMatrix<T>&& obj2);
		~templateMatrix<T>();

		int GetRow() const;
		int GetCol() const;
		int GetId() const;
		static int GetCount();
		const T& FindMax() const;
		const T& FindMin() const;
		int GetSize() const;
		bool CheckMul(const templateMatrix<T>& m2) const;
		bool CheckSum(const templateMatrix<T>& m2) const;
		templateMatrix<T>& operator = (const templateMatrix<T>& other);
		templateMatrix<T>& operator = (templateMatrix<T>&& other);
		templateMatrix<T>& operator += (const templateMatrix<T>& other);
		templateMatrix<T>& operator -= (const templateMatrix<T>& other);
		templateMatrix<T>& operator *= (const templateMatrix<T>& other);
		templateMatrix<T>& operator *= (const T& k);
		friend ostream& operator << <T>(ostream& output, const templateMatrix<T>& m);

		friend templateMatrix<T> operator+<T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend templateMatrix<T> operator-<T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend templateMatrix<T> operator*<T>(const templateMatrix<T>& m1, const T& k);
		friend templateMatrix<T> operator*<T>(const T& k, const templateMatrix<T>& m1);
		friend templateMatrix<T> operator*<T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);

		friend bool operator == <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend bool operator != <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend bool operator < <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend bool operator > <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend bool operator <= <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);
		friend bool operator >= <T>(const templateMatrix<T>& m1, const templateMatrix<T>& m2);


	};

	template<typename T>
	int templateMatrix<T>::count = 0;

	template<typename T>
	templateMatrix<T>::templateMatrix() :templateMatrix<T>::templateMatrix(0, 0, NULL) {}

	template<typename T>
	templateMatrix<T>::templateMatrix(int _row , const T* mtrx) : templateMatrix<T>::templateMatrix(_row , _row , mtrx) {}

	template<typename T>
	templateMatrix<T>::templateMatrix(int _row , int _col, const T* mtrx)
	{
		count++;
		id = count;
		if (_row  < 0 || _col < 0) 
			throw("Размер не может быть отрицательный! " + to_string(id));
		row = _row ;
		col = _col;
		matrix = (row * col) ? (new T[row * col]) : NULL;

		if (mtrx)
			for (int i = 0; i < row * col; i++)
				matrix[i] = mtrx[i];
		else
			for (int i = 0; i < row * col; i++)
				matrix[i] = T();
	}

	template<typename T>
	templateMatrix<T>::templateMatrix(const templateMatrix<T>& obj2) : templateMatrix<T>::templateMatrix(obj2.row, obj2.col, obj2.matrix)
	{}

	template<typename T>
	templateMatrix<T>::templateMatrix(templateMatrix<T>&& obj2) : templateMatrix<T>::templateMatrix()
	{
		operator=(obj2);
	}

	template<typename T>
	templateMatrix<T>::~templateMatrix()
	{
		row = 0;
		col = 0;
		if (matrix != 0)
			delete[]matrix;
	}

	template<typename T>
	int templateMatrix<T>::GetRow() const
	{
		return row;
	}

	template<typename T>
	int templateMatrix<T>::GetCol() const
	{
		return col;
	}

	template<typename T>
	int templateMatrix<T>::GetId() const
	{
		return id;
	}

	template<typename T>
	int templateMatrix<T>::GetCount()
	{
		return count;
	}

	template<typename T>
	T& templateMatrix<T>::Index::operator[](int j)
	{
		if (j < 0 || col <= j) 
			throw ("Неверный индекс [][!]  " + to_string(id));
		return arr[j];
	}

	template<typename T>
	const T& templateMatrix<T>::Index::operator[](int j) const
	{
		if (j < 0 || col <= j) 
			throw ("Неверный индекс [][!]  " + to_string(id));
		return arr[j];
	}

	template<typename T>
	typename templateMatrix<T>::Index templateMatrix<T>::operator[](int i)
	{
		if ((i < 0) || (row <= i)) 
			throw ("Неверный индекс [!][]  " + to_string(id));
		return Index(matrix + i * col, col, id);
	}


	template<typename T>
	const typename templateMatrix<T>::Index templateMatrix<T>::operator[](int i) const
	{
		if ((i < 0) || (row <= i)) 
			throw ("Неверный индекс [!][]  " + to_string(id));
		return Index(matrix + i * col, col, id);
	}

	template<typename T>
	templateMatrix<T>::Index::Index(T* _arr, int i, int _id) 
	{
		arr = _arr;
		col = i;
		id = _id;
	}

	template<typename T>
	templateMatrix<T>::Index::~Index()
	{
		arr = NULL;
	}

	template<typename T>
	const T& templateMatrix<T>::FindMax() const
	{
		if (matrix == 0)
			throw ("Матрица " + to_string(id) + " пустая ");
		int max = 0;
		for (int i = 1; i < row * col; i++)
		{
			if (matrix[i] > matrix[max]) 
				max = i;
		}
		return matrix[max];
	}

	template<typename T>
	const T& templateMatrix<T>::FindMin() const
	{
		if (matrix == 0) 
			throw ("Матрица " + to_string(id) + " пустая ");
		int min = 0;
		for (int i = 1; i < row * col; i++)
		{
			if (matrix[i] < matrix[min])
				min = i;
		}
		return matrix[min];
	}

	template<typename T>
	int templateMatrix<T>::GetSize() const
	{
		return row * col;
	}

	template<typename T>
	bool templateMatrix<T>::CheckMul(const templateMatrix<T>& m2) const
	{
		return col == m2.row;
	}
	template<typename T>
	bool templateMatrix<T>::CheckSum(const templateMatrix<T>& m2) const
	{
		return ((row == m2.row) && (col == m2.col));
	}
	template<typename T>
	templateMatrix<T>& templateMatrix<T>::operator=(const templateMatrix<T>& other)
	{
		if (this != &other)
		{
			if (GetSize() != other.GetSize())
			{
				if (matrix)
				{
					delete[] matrix;
					matrix = nullptr;
				}
				if (other.GetSize() > 0)
					matrix = new T[other.GetSize()];
			}
			row = other.row;
			col = other.col;
			for (int i = 0; i < row * col; i++)
			{
				matrix[i] = other.matrix[i];
			}
		}
		return *this;
	}
	template<typename T>
	templateMatrix<T>& templateMatrix<T>::operator=(templateMatrix<T>&& other)
	{
		if (this != &other)
		{
			swap(matrix, other.matrix);
			swap(row, other.row);
			swap(col, other.col);
		}
		return *this;
	}
	template<typename T>
	templateMatrix<T>& templateMatrix<T>::operator+=(const templateMatrix<T>& other)
	{
		if (!CheckSum(other)) 
			throw ("Вычислить сумму матриц " + to_string(id) + " и " + to_string(other.id))+ " невозможно!";
		for (int i = 0; i < row * col; i++)
		{
			matrix[i] += other.matrix[i];
		}
		return *this;
	}
	template<typename T>
	templateMatrix<T>& templateMatrix<T>::operator-=(const templateMatrix<T>& other)
	{
		if (!CheckSum(other))
			throw ("Вычислить разность матриц " + to_string(id) + " и " + to_string(other.id) + " невозможно!");
		for (int i = 0; i < row * col; i++)
		{
			matrix[i] -= other.matrix[i];
		}
		return *this;
	}
	template<typename T>
	templateMatrix<T>& templateMatrix<T>::operator*=(const templateMatrix<T>& other)
	{
		if (!CheckMul(other))
			throw ("Вычислить произведение матриц " + to_string(id) + "  и " + to_string(other.id) + " невозможно!");
		templateMatrix<T> fortime(row, other.col);
		for (int i = 0; i < fortime.row; i++)
		{
			for (int j = 0; j < fortime.col; j++)
			{
				fortime.matrix[i * fortime.col + j] = (matrix[i * col + 0] * other.matrix[0 * other.col + j]);
				for (int k = 1; k < col; k++)
					fortime.matrix[i * fortime.col + j] += (matrix[i * col + k] * other.matrix[k * other.col + j]);
			}
		}
		*this = move(fortime);
		return *this;
	}
	template<typename T>
	typename templateMatrix<T>& templateMatrix<T>::operator*=(const T& k)
	{
		for (int i = 0; i < row * col; i++)
		{
			matrix[i] *= k;
		}
		return *this;
	}

	template<typename T>
	bool operator < (const templateMatrix<T>& m1, const templateMatrix<T>& m2)
	{
		return m1.GetSize() < m2.GetSize();
	}
}