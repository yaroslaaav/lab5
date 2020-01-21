#pragma once
namespace Math
{
	class Matrix
	{
	private:
		double* matrix;
		int row;
		int col;

		int id;
		static int count;
		class Index
		{
		private:
			double* arr;
			int col;
			int id;
		public:
			Index(double*, int, int);			
			~Index();	
			double operator [] (int index) const;
			double& operator [] (int index);
		};
	public:
		Index operator[](int i);
		const Index operator[](const int i) const;
		Matrix();
		explicit Matrix(int _row, const double* mtrx=NULL);
		Matrix(int _row, int _col, const double* mtrx = NULL);
		Matrix(const Matrix& obj2);
		Matrix(Matrix&& obj2);
		~Matrix();

		int GetRow() const;
		int GetCol() const;
		int GetId() const;
		static int GetCount();
		double FindMax() const;
		double FindMin() const;
		int GetSize() const;
		bool CheckMul(const Matrix& m2) const;
		bool CheckSum(const Matrix& m2) const;
		Matrix& operator = (const Matrix& other);
		Matrix& operator = (Matrix&& other);
		Matrix& operator += (const Matrix& other);
		Matrix& operator -= (const Matrix& other);
		Matrix& operator *= (const Matrix& other);
		Matrix& operator *= (double k);

		friend std::ostream& operator<<(std::ostream& s, const Matrix& m);
		friend Matrix operator+(const Matrix& m1, const Matrix& m2);
		friend Matrix operator-(const Matrix& m1, const Matrix& m2);
		friend Matrix operator*(const Matrix& m1, double k);
		friend Matrix operator*(double k, const Matrix& m1);
		friend Matrix operator*(const Matrix& m1, const Matrix& m2);

		friend bool operator == (const Matrix& obj1, const Matrix& obj2);
		friend bool operator != (const Matrix& obj1, const Matrix& obj2);
		friend bool operator >= (const Matrix& obj1, const Matrix& obj2);
		friend bool operator <= (const Matrix& obj1, const Matrix& obj2);
		friend bool operator > (const Matrix& obj1, const Matrix& obj2);
		friend bool operator < (const Matrix& obj1, const Matrix& obj2);
	};
}
