// ЛАБ5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"

#include "templateMatrix.h"
#include "Matrix.h"
#include "Fraction.h"

using namespace Math;
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	try 
	{
		/*double arr[4]{ 2,1,1,1 };
		templateMatrix<double> temparr[4];
		temparr[0] = templateMatrix<double>(2, 2, arr);
		temparr[1] = templateMatrix<double>(2, 2, arr);
		temparr[2] = templateMatrix<double>(2, 2, arr);
		temparr[3] = templateMatrix<double>(2, 2, arr);
		templateMatrix < templateMatrix < double>> m1(2, 2, temparr);
		templateMatrix < templateMatrix < double>> m2(2, 2, temparr);
		cout << m1 + m2 << "--------------------" << endl;
		cout << m1 - m2 << "--------------------" << endl;
		cout << m1 * m2 << "--------------------" << endl;*/
		Fraction fraction_brr[4];
		fraction_brr[0] = Fraction(3, 4);
		fraction_brr[1] = Fraction(2, 2);
		fraction_brr[2] = Fraction(2, 1);
		fraction_brr[3] = Fraction(4, 2);
		templateMatrix<Fraction> m1(2, 2, fraction_brr);
		templateMatrix<Fraction> m2(2, 2, fraction_brr);
		cout << m1 + m2 << "--------------------" << endl;
		cout << m1 - m2 << "--------------------" << endl;
		cout << m1 * m2 << "--------------------" << endl; 
	}
	catch (const string ex)
	{
		cout << ex << endl;
	}
}

