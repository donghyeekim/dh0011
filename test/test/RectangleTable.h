/**
* Mike Knee 09/01/2017
*
* Header file for the RectangleTable class.
*/

#ifndef _RECTANGLETABLE_H
#define _RECTANGLETABLE_H

#include "ITable.h"

/**
* Rectangular billiard table class. Inherits from ITable.
*/
class RectangleTable : public ITable
{
public:
	/**
	* Empty constructor, does not provide default values.
	*/
	RectangleTable();
	/**
	* Double value constructor, assigns length of rectangle to 2x and
	* width of rectangle to 2y.
	*/
	RectangleTable(double x, double y);
	/**
	* Destructor, does nothing as no heap memory is used.
	*/
	~RectangleTable();

	// Getters and setters.
	double GetX() const { return fX; }
	double GetY() const { return fY; }
	void SetX(double x);
	void SetY(double y);

	// Methods implemented from ITable.
	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);
private:
	// Dimensions of the table, parameterised by fX and fY. Length of table
	// is 2fX and width is 2fY. Centre is at (0,0).
	double fX;
	double fY;
};

#endif
