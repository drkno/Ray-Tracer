/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Plane class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_PLANE
#define H_PLANE

#include "../types/Vector.h"
#include "Object.h"

#define GRIDX 15
#define GRIDZ 15

class Plane : public Object
{
private:
    Vector a, b, c, d;      //The 4 vertices of a quad
	Colour colorB;

public:	
	Plane(void);
    Plane(Vector pa, Vector pb, Vector pc, Vector pd, Colour colA, Colour colB)
		: a(pa), b(pb), c(pc), d(pd)
	{
		color = colA;
		colorB = colB;
	};
	bool isInside(Vector);
	float intersect(Vector, Vector);
	Vector normal(Vector);
	Colour getColour(Vector);
};

#endif //!H_PLANE
