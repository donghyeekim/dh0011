/**
* Mike Knee 10/01/2017
*
* Source file for the LorentzTable class.
*/

#include <cmath>
#include <cstdio>

#include "LorentzTable.h"

LorentzTable::LorentzTable()
{}
LorentzTable::LorentzTable(double x, double y, double radius) :
fX(x), fY(y), fRadius(radius)
{}
LorentzTable::~LorentzTable()
{}

void LorentzTable::SetX(double x)
{
	if (x > 0)
	{
		fX = x;
		return;
	}
}

void LorentzTable::SetY(double y)
{
	if (y > 0)
	{
		fY = y;
		return;
	}
}

void LorentzTable::SetRadius(double radius)
{
	if (radius > 0 && radius < fY && radius < fX)
	{
		fRadius = radius;
		return;
	}
}

double LorentzTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	Vector norm;
	double temp;

	//As rectangle, except final case.
	if (collision.fX == fX)
	{
		// Check corner cases.
		if (collision.fY == fY)
		{
			norm = Vector(-std::sqrt(2), -std::sqrt(2));
		}
		else if (collision.fY == -fY)
		{
			norm = Vector(-std::sqrt(2), std::sqrt(2));
		}
		norm = Vector(-1, 0);
	}
	else if (collision.fX == -fX)
	{
		if (collision.fY == fY)
		{
			norm = Vector(std::sqrt(2), -std::sqrt(2));
		}
		else if (collision.fY == -fY)
		{
			norm = Vector(std::sqrt(2), std::sqrt(2));
		}
		norm = Vector(1, 0);
	}
	// No need to check corner cases now, as they would already have been caught.
	else if (collision.fY == fY)
		norm = Vector(0, -1);
	else if (collision.fY == -fY)
		norm = Vector(0, 1);
	else
		//Hasn't hit a wall, must have hit centre circle:
		norm = collision / collision.Mod();

	// Reflect velocity in surface normal.
	temp = norm.Arg() - velocity.Arg();
	return temp;
}

Vector LorentzTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	Vector temp, norm;

	//As rectangle, but final circular case different.
	if (collision.fX == fX)
	{
		// Check corner cases.
		if (collision.fY == fY)
		{
			norm = Vector(-std::sqrt(2), -std::sqrt(2));
		}
		else if (collision.fY == -fY)
		{
			norm = Vector(-std::sqrt(2), std::sqrt(2));
		}
		norm = Vector(-1, 0);
	}
	else if (collision.fX == -fX)
	{
		if (collision.fY == fY)
		{
			norm = Vector(std::sqrt(2), -std::sqrt(2));
		}
		else if (collision.fY == -fY)
		{
			norm = Vector(std::sqrt(2), std::sqrt(2));
		}
		norm = Vector(1, 0);
	}
	// No need to check corner cases now, as they would already have been caught.
	else if (collision.fY == fY)
		norm = Vector(0, -1);
	else if (collision.fY == -fY)
		norm = Vector(0, 1);
	else
		//Hasn't hit a wall, must have collided with circle. (different with RectangleTable)
		norm = collision / collision.Mod();

	// Reflect velocity in surface normal.
	temp = velocity - 2 * velocity.Dot(norm)*norm;
	return temp;
}

Vector LorentzTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	double gamma = 0;

	double a, b, c;

	a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
	b = 2 * (initial.fX * velocity.fX + initial.fY * velocity.fY);
	c = initial.fX * initial.fX + initial.fY * initial.fY - fRadius * fRadius;


	//Check for collision with circle first.
	if (b * b - 4 * a * c > 0)
	{
		gamma = (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a);
		if (gamma > 0)
			return initial + gamma * velocity;
	}
	if (velocity.fY > 0)
		// Set y = fY:
	{
		//p = i + gv, solving for g.
		gamma = (fY - initial.fY) / velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, fY);
		}
	}
	else if (velocity.fY < 0)
		// Set y = -fY:
	{
		gamma = (-fY - initial.fY) / velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, -fY);
		}
	}

	// Setting y = fY has gone out of bounds, so now set x = fX:
	if (velocity.fX > 0)
		// x = fX:
	{
		gamma = (fX - initial.fX) / velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		return Vector(fX, y);
	}
	else if (velocity.fX < 0)
		// x = -fX:
	{
		gamma = (-fX - initial.fX) / velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		return Vector(-fX, y);
	}

	return Vector(0, 0);
}
