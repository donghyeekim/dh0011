/**
* Mike Knee 09/01/2017
*
* Source file for the RectangleTable class.
*/

#include <cmath>

#include "RectangleTable.h"

RectangleTable::RectangleTable()
{}

RectangleTable::RectangleTable(double x, double y) :
fX(x), fY(y)
{}

RectangleTable::~RectangleTable()
{}

void RectangleTable::SetX(double x)
{
	// Only set if greater than 0, no expection or error thrown.
	// (This is because this class is never expected to see the outside
	// world, and I expect I can remember to initialise things properly.)
	if (x > 0) fX = x;

	return;
}

void RectangleTable::SetY(double y)
{
	if (y > 0) fY = y;

	return;
}

double RectangleTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	if (collision.fX == fX)
	{
		// Check corner cases.
		if (collision.fY == fY)
		{
			return -3 * M_PI - velocity.Arg();
		}
		else if (collision.fY == -fY)
		{
			return 3 * M_PI / 4 - velocity.Arg();
		}
		return M_PI - velocity.Arg();
	}
	else if (collision.fX == -fX)
	{
		if (collision.fY == fY)
		{
			return -M_PI / 4 - velocity.Arg();
		}
		else if (collision.fY == -fY)
		{
			return M_PI / 4 - velocity.Arg();
		}
		return -velocity.Arg();
	}
	// No need to check corner cases now, as they would already have been caught.
	else if (collision.fY == fY)
		return -M_PI / 2 - velocity.Arg();
	else if (collision.fY == -fY)
		return M_PI / 2 - velocity.Arg();

	return 0;
}

Vector RectangleTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	Vector temp, norm;

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

	// Reflect velocity in surface normal.
	temp = velocity - 2 * velocity.Dot(norm)*norm;
	return temp;
}

Vector RectangleTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	double gamma;

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
