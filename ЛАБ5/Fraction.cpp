#include "stdafx.h"
#include "Fraction.h"

using namespace std;
using namespace Math;

void Fraction::Reduction()
{
	if (denom == 0)
		throw string("«наменатель не может быть равен 0!");
	if (denom < 0)
	{
		denom = -denom;
		num = -num;
	}
	if (num == 0)
		denom = 1;
	else
	{
		int tempDenom = denom,
			tempNum = num;
		if (tempNum < 0)
			tempNum = -tempNum;

		int	ost = tempDenom % tempNum;
		while (ost != 0)
		{
			tempDenom = tempNum;
			tempNum = ost;
			ost = tempDenom % tempNum;
		}
		int nod = tempNum;
		if (nod != 1)
		{
			num /= nod;
			denom /= nod;
		}
	}
}

Fraction Fraction::GetRem()
{
	return Fraction(num % denom, denom);
}

int Fraction::NOK(int num1, int num2) const
{
	return num1 * num2 / NOD(num1, num2);
}

int Fraction::NOD(int num1, int num2) const
{
	int n1 = num1;
	int n2 = num2;
	while (n1 != n2)
	{
		if (n1 > n2)
			n1 -= n2;
		else
			n2 -= n1;
	}
	return n1;
}

int Fraction::GetNum() const
{
	return num;
}

int Fraction::GetDenom() const
{
	return denom;
}

int Fraction::GetIntPart()
{
	int intPart = 0;
	int tempNum = num, tempDenom = denom;
	if (tempNum < 0) tempNum *= -1;
	if (tempNum >= tempDenom)
	{
		intPart += (tempNum / tempDenom);
		if (num < 0)
		{
			intPart *= -1;
		}
	}
	return intPart;
}

Fraction::Fraction() : Fraction(0, 0, 1)
{
}

Fraction::Fraction(int n1) : Fraction(0, n1, 1)
{
}

Fraction::Fraction(int n1, int n2) : Fraction(0, n1, n2)
{
}

Fraction::Fraction(int intPart, int n1, int n2) : num(n1), denom(n2)
{
	if (intPart && (n1 < 0 || n2 < 0))
		throw (string)"“олько цела€ часть может быть отрицательной!";
	if (denom == 0)
		throw (string)"«наменатель не должен быть равен 0!";
	if (intPart && intPart != 0)
	{
		if (intPart < 0)
		{
			intPart *= -1;
			num += intPart * denom;
			num *= -1;
		}
		else
		{
			num += intPart * denom;
		}
	}
	if (denom < 0)
	{
		denom *= -1;
		num *= -1;
	}
	Reduction();

}

Fraction& Fraction::operator+=(const Fraction& frac1)
{
	int tempDenom = NOK(denom, frac1.denom);
	num = ((tempDenom / denom) * num);
	denom = tempDenom;
	num += ((frac1.num) * (tempDenom / frac1.denom));

	Reduction();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& frac1)
{
	int tempDenom = NOK(denom, frac1.denom);
	num = ((tempDenom / denom) * num);
	denom = tempDenom;
	num -= ((frac1.num) * (tempDenom / frac1.denom));

	Reduction();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& frac1)
{
	int tempNum = NOD(num, frac1.denom);
	int tempDen = NOD(denom, frac1.num);
	num /= tempNum;
	denom /= tempDen;
	num *= (frac1.num / tempDen);
	denom *= (frac1.denom / tempNum);

	Reduction();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& frac1)
{
	int tempNum = NOD(num, frac1.num);
	int tempDen = NOD(denom, frac1.denom);
	num /= tempNum;
	denom /= tempDen;
	num *= (frac1.denom / tempDen);
	denom *= (frac1.num / tempNum);

	Reduction();
	return *this;
}

Fraction& Fraction::operator*=(double k)
{
	num *= k;

	Reduction();
	return *this;
}

Fraction Math::operator+(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) += frac2;
}

Fraction Math::operator-(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) -= frac2;
}

Fraction Math::operator*(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) *= frac2;
}

Fraction Math::operator/(const Fraction& frac1, const Fraction& frac2)
{
	return Fraction(frac1) /= frac2;
}

Fraction Math::operator*(const Fraction& frac1, double k)
{
	return Fraction(frac1) *= k;
}

Fraction Math::operator*(double k, const Fraction& frac1)
{
	return operator*(frac1, k);
}



ostream& Math::operator<<(ostream& output, const Fraction& frac1)
{

	if ((frac1.denom != 1) && (frac1.num != 0))
		cout << " " << frac1.num << "/" << frac1.denom;
	else
		cout << frac1.num;
	return output;
}