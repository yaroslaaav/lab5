#pragma once
namespace Math
{

	class Fraction
	{
	private:
		int num;
		int denom;
	public:

		Fraction();
		explicit Fraction(int);
		Fraction(int, int);
		Fraction(int, int, int);
	
		void Reduction();
		int GetIntPart();
		Fraction GetRem();
		int NOK(int, int) const;
		int NOD(int, int) const;
		int GetNum() const;
		int GetDenom() const;
		Fraction& operator += (const Fraction&);
		Fraction& operator -= (const Fraction&);
		Fraction& operator *= (const Fraction&);
		Fraction& operator /= (const Fraction&);
		Fraction& operator *= (double k);

		friend Fraction operator + (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator - (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator * (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator / (const Fraction& frac1, const Fraction& frac2);
		friend Fraction operator*(const Fraction& frac1, double k);
		friend Fraction operator*(double k, const Fraction& frac1);

		friend std::ostream& operator<<(std::ostream& output, const Fraction& frac1);


	};
}
