#include "ChequeredFloor.h"

ChequeredFloor::ChequeredFloor(Vector pa, Vector pb, Vector pc, Vector pd, Colour colA, Colour colB)
{
	a = pa;
	b = pb;
	c = pc;
	d = pd;
	color = colA;
	colorB = colB;
};

Colour ChequeredFloor::getColour(Vector pos)
{
	float x = (a - b).x / GRIDX;
	float z = (b - c).z / GRIDZ;

	int posX = (pos.x - a.x) / x;
	int posZ = (pos.z - b.z) / z;

	if ((posX % 2 == 0 || posZ % 2 == 0) && posX % 2 != posZ % 2)
	{
		return color;
	}
	return colorB;
}

//Function to test if an input point is within the quad.
bool ChequeredFloor::isInside(Vector q)
{
	Vector n = normal(q);
	Vector ua = b - a, ub = c - b, uc = d - c, ud = a - d;
	Vector va = q - a, vb = q - b, vc = q - c, vd = q - d;

	return ua.cross(va).dot(n) >= 0 && ub.cross(vb).dot(n) >= 0
		&& uc.cross(vc).dot(n) >= 0 && ud.cross(vd).dot(n) >= 0;
}

//Function to compute the paramter t at the point of intersection.
float ChequeredFloor::intersect(Vector pos, Vector dir)
{
	Vector n = normal(pos);
	Vector vdif = a - pos;
	float vdotn = dir.dot(n);
	if (fabs(vdotn) < 1.e-4) return -1;
	float t = vdif.dot(n) / vdotn;
	if (fabs(t) < 0.0001) return -1;
	Vector q = pos + dir*t;
	return isInside(q) ? t : -1;
}

// Function to compute the unit normal vector
// Remember to output a normalised vector!
Vector ChequeredFloor::normal(Vector pos)
{
	return (b - a).cross(c - a);
}