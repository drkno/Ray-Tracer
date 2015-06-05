#include "Cylinder.h"

Cylinder::Cylinder(Vector center, float height, float radius, Colour colour) : Object()
{
	this->color = colour;
	this->radius = radius;
	this->height = height;
	this->heightMax = center.y + height / 2;
	this->heightMin = center.y - height / 2;
	this->center = center;
}

// Base on algorithm from:
// http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf
float Cylinder::intersect(Vector pos, Vector dir)
{
	auto posxc = pos.x - center.x;
	auto poszc = pos.z - center.z;
	auto a = powf(dir.z, 2) + powf(dir.x, 2);
	auto b = poszc * dir.z + posxc * dir.x;
	b *= (-2);
	auto c = powf(posxc, 2) + powf(poszc, 2) - powf(radius, 2);

	// b^2 - 4ac
	auto root = powf(b, 2) - 4 * a * c;
	// cannot root at -ve numbers
	if (root <= 0.0)
	{
		return -1;
	}

	root = sqrtf(root);
	a *= 2;

	// solve for min t
	float t[2];
	t[0] = (b - root) / a;
	t[1] = (b + root) / a;
	t[0] = min(t[0], t[1]);

	auto yVal = dir.y * t[0] + pos.y;
	if (yVal < heightMax && yVal > heightMin)
	{
		return t[0];
	}
	yVal = dir.y * t[1] + pos.y;
	/*if (yVal < heightMax && yVal > heightMin)
	{
		return t[1];
	}

	/ * / caps
	yVal = dir.y * t[1] + pos.y;
	if (yVal < heightMax && yVal > heightMin)
	{
		yVal =- center.y;
		Vector normal(0, (yVal < 0) ? -1 : 1, 0);
		auto nDotd = normal.dot(dir);
		Vector planeCenter = center;
		planeCenter.y = heightMax;
		return (planeCenter - pos).dot(normal) / nDotd;
	}*/

	return -1;
}

Vector Cylinder::normal(Vector pos)
{
	Vector n;
	float rad = sqrtf(powf(pos.x - center.x, 2) + powf(pos.z - center.z, 2));
	n = Vector(pos.x - center.x, 0, pos.z - center.z);
	n.normalise();
	return n;
}
