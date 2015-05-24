#include "Cube.h"

/**
* Cube's intersection method.  The input is a ray (pos, dir).
*/
float Cube::intersect(Vector pos, Vector dir)
{
	// todo: fixme: change this

	float tx1, tx2, ty1, ty2, tz1, tz2, tmin, tmax;
	tx1 = (xmin - pos.x) / dir.x;
	tx2 = (xmax - pos.x) / dir.x;
	ty1 = (ymin - pos.y) / dir.y;
	ty2 = (ymax - pos.y) / dir.y;
	tz1 = (zmin - pos.z) / dir.z;
	tz2 = (zmax - pos.z) / dir.z;

	tmin = std::max(std::min(tx1, tx2), std::max(std::min(ty1, ty2), std::min(tz1, tz2)));
	tmax = std::min(std::max(tx1, tx2), std::min(std::max(ty1, ty2), std::max(tz1, tz2)));

	if (tmin < tmax) {
		return tmin;
	}
	else {
		return -1;
	}
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the cube.
*/
Vector Cube::normal(Vector p)
{
	// todo: fixme: change this

	Vector max(xmax, ymax, zmax);
	Vector min(xmin, ymin, zmin);
	Vector center = (max + min) / 2;
	Vector n = p - center;
	float largest = std::max(fabs(n.x), std::max(fabs(n.y), fabs(n.z)));
	if (fabs(n.x) == largest) {
		n.y = 0.0;
		n.z = 0.0;
	}
	else if (fabs(n.y) == largest) {
		n.x = 0.0;
		n.z = 0.0;
	}
	else if (fabs(n.z) == largest) {
		n.x = 0.0;
		n.y = 0.0;
	}
	n.normalise();
	return n;
}

Cube::Cube(Vector corner1, Vector corner2, Colour color)
{
	this->color = color;
	xmin = std::min(corner1.x, corner2.x);
	xmax = std::max(corner1.x, corner2.x);
	ymin = std::min(corner1.y, corner2.y);
	ymax = std::max(corner1.y, corner2.y);
	zmin = std::min(corner1.z, corner2.z);
	zmax = std::max(corner1.z, corner2.z);
}