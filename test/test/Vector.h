/**
* Mike Knee 09/01/2017
*
* Header file for the Vector class.
*/

#ifndef _VECTOR_H
#define _VECTOR_H

/**
* Class for 2 dimensional vectors, with all usual vector operations defined.
*/
class Vector
{
public:
	/**
	* Empty constructor, does not provide any default values.
	*/
	Vector();
	/**
	* Double value constructor, assigns fX(x) and fY(y).
	*/
	Vector(double x, double y);
	/**
	* Copy constructor, vector returned is equal to other.
	*/
	Vector(const Vector & other);
	/**
	* Destructor, does nothing as no heap memory is used by the class.
	*/
	~Vector();

	// Addition Operators.
	Vector operator+(const Vector & other) const { return Vector(fX + other.fX, fY + other.fY); }
	Vector operator-() const { return Vector(-fX, -fY); }
	Vector operator-(const Vector & other) const { return *this + (-other); }

	// Scalar operators.
	Vector operator*(double mult) const { return Vector(fX * mult, fY * mult); }
	Vector operator/(double div) const { return Vector(fX / div, fY / div); }
	friend Vector operator*(double lhs, const Vector & rhs);

	// Equality and assignment.
	bool operator==(const Vector & other) const;
	Vector & operator=(const Vector & other);

	/**
	* Returns the dot product of the vector with other.
	*
	* Vector & other: vector to dot product this with.
	* return: double result of dot product this with other.
	*/
	double Dot(const Vector & other) const;
	/**
	* Argument of the vector.
	*
	* return: argument of this in radians.
	*/
	double Arg() const;
	/**
	* Modulus of the vector.
	*
	* return: scalar modulus of the vector sqrt(fX * fX + fY * fY).
	*/
	double Mod() const;
	/**
	* Normalised version of vector.
	*
	* return: normal vector with same argument as this.
	*/
	Vector Norm() const;
	/**
	* Rotates vector around angle.
	*
	* return: vector this rotated around angle in radians.
	*/
	Vector Rotate(double angle) const;

	// Member variables are public, as access restrictions are not necessary.
	// Class is not being used outside here, and variables can
	// realistically take any possible double value, so allowing them to be
	// directly assigned is acceptable.
	double fX;
	double fY;
};

#endif
