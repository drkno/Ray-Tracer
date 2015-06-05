/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Plane class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Plane.h"

Plane::Plane(Vector pa, Vector pb, Vector pc, Vector pd, Colour col)
{
	a = pa;
	b = pb;
	c = pc;
	d = pd;
	color = col;
}

//Function to test if an input point is within the quad.
bool Plane::isInside(Vector q)
{
	Vector n = normal(q);
	Vector ua = b-a,  ub = c-b, uc = d-c, ud = a-d;
	Vector va = q-a,  vb = q-b, vc = q-c, vd = q-d;

	return ua.cross(va).dot(n) >= 0 && ub.cross(vb).dot(n) >= 0
		&& uc.cross(vc).dot(n) >= 0 && ud.cross(vd).dot(n) >= 0;
}

//Function to compute the paramter t at the point of intersection.
float Plane::intersect(Vector pos, Vector dir)
{
	Vector n = normal(pos);
	Vector vdif = a-pos;
	float vdotn = dir.dot(n);
	if(fabs(vdotn) < 1.e-4) return -1;
    float t = vdif.dot(n)/vdotn;
	if(fabs(t) < 0.0001) return -1;
	Vector q = pos + dir*t;
	return isInside(q) ? t : -1;
}

// Function to compute the unit normal vector
// Remember to output a normalised vector!
Vector Plane::normal(Vector pos)
{
	return (b - a).cross(c - a);
}

