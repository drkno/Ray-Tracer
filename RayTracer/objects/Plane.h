/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Plane class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#pragma once

#include "../types/Vector.h"
#include "Object.h"

class Plane : public Object
{
protected:
    Vector a, b, c, d;      //The 4 vertices of a quad

public:	
	Plane(void);
	Plane(Vector, Vector, Vector, Vector, Colour);
	bool isInside(Vector);
	float intersect(Vector, Vector);
	Vector normal(Vector);
};
