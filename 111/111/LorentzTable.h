/**
* Mike Knee 10/01/2017
*
* Header file for the LorentzTable class.
*/

#include "ITable.h"

/**
* LorentzTable class, inherits from ITable.
*/
class LorentzTable : public ITable
{
public:
	/**
	* Empty constructor
	*/
	LorentzTable();
	/**
	* Three value constructor, rectangle is height x and width y, inner
	* circle radius radius.
	*/
	LorentzTable(double x, double y, double radius);
	/**
	* Empty desctructor, no heap memory used.
	*/
	~LorentzTable();

	//Getters and setters.
	double GetX() const { return fX; }
	double GetY() const { return fY; }
	double GetRadius() const { return fRadius; }
	void SetX(double x);
	void SetY(double y);
	void SetRadius(double radius);

	//Functions implemented from ITable.
	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);

private:
	//Private members.
	double fX;
	double fY;
	double fRadius;
};
