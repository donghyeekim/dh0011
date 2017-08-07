/**
* Mike Knee 09/01/2016
*
* Header file for the ITable interface.
*/

#ifndef _ITABLE_H
#define _ITABLE_H

#define M_PI 3.141592653589793238

/**
* Interface for all billiard tables.
*
* Though not mandated by this interface, all tables should have a centre at
* 0,0.
*/

#include "Vector.h"

class ITable
{
public:
	// Always put in a virtual destructor...
	virtual ~ITable() {}

	/**
	* AngleIncidence returns the angle to rotate the velocity onto the
	* negative normal. Very useful for some things...
	*
	* Vector & collision: point of collision with the wall of the table.
	* Vector & velocity: vector velocity of the ball.
	* return: angle between the velocity and the negative suraface normal
	* which is almost useful.
	*/
	virtual double AngleIncidence(const Vector & collision, const Vector & velocity) = 0;

	/**
	* Reflects the vector velocity off the surface at normal at point
	* collision.
	*
	* Vector & collision: point of collision with the wall of the table.
	* Vector & velocity: vector velocity of the ball.
	* return: vector velocity after collision with table at point
	* specified by collision.
	*/
	virtual Vector ReflectVector(const Vector & collision, const Vector & velocity) = 0;

	/**
	* CollisionPoint returns the point on the table edge that the ball
	* collides at.
	*
	* Vector & initial: start point of the ball.
	* Vector & velocity: vector velocity of the ball.
	* return: vector position of collision with the table edge.
	*/
	virtual Vector CollisionPoint(const Vector & initial, const Vector & velocity) = 0;
};

#endif
