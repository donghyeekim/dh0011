/**
* Mike Knee 09/01/2017
*
* Source file for the Vector class.
*/
#include "Vector.h"

#include <cmath>

Vector::Vector()
{}

Vector::Vector(double x, double y) :
fX(x), fY(y)
{}

Vector::Vector(const Vector & other) :
fX(other.fX), fY(other.fY)
{}

Vector::~Vector()
{}

double Vector::Dot(const Vector & other) const
{
	return fX * other.fX + fY * other.fY;
}

double Vector::Arg() const
{
	//Vector argument.
	return std::atan(fY / fX);
}

double Vector::Mod() const
{
	//Vector modulus.
	return std::sqrt(fX * fX + fY * fY);
}

Vector Vector::Norm() const
{
	//Vector normal.
	return Vector(fX / this->Mod(), fY / this->Mod());
}

Vector Vector::Rotate(double angle) const
{
	//Rotation using matrix.
	return Vector(fX * cos(angle) - fY * sin(angle), fX * sin(angle) + fY * cos(angle));
}

Vector operator*(double lhs, const Vector & rhs)
{
	return Vector(lhs * rhs.fX, lhs * rhs.fY);
}

bool Vector::operator==(const Vector & other) const
{
	if (fX == other.fX && fY == other.fY)
		return true;
	else
		return false;
}

Vector & Vector::operator=(const Vector & other)
{
	this->fX = other.fX;
	this->fY = other.fY;
	return *this;
}
