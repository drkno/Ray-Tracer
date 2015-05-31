#include "Cube.h"

/*
Implementation based off the Ray-Box method described here:
http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm
*/
float Cube::intersect(Vector pos, Vector dir)
{
	auto minv = (minVector - pos) / dir;
	auto maxv = (maxVector - pos) / dir;

	if (minv.x > maxv.x) swap(minv.x, maxv.x);
	if (minv.y > maxv.y) swap(minv.y, maxv.y);
	if (minv.z > maxv.z) swap(minv.z, maxv.z);

	auto mint = max(minv.x, max(minv.y, minv.z));
	auto maxt = min(maxv.x, min(maxv.y, maxv.z));

	return mint < maxt ? mint : -1;
}

Vector Cube::normal(Vector point)
{
	const float tollerance = 0.000001;
	auto n = point - center;
	auto maxx = fabs(n.x);
	auto maxy = fabs(n.y);
	auto maxz = fabs(n.z);

	auto maxDir = max(maxx, maxy);
	maxDir = max(maxDir, maxz);

	if (maxx < maxDir + tollerance && maxx > maxDir - tollerance) {
		n.y = 0.0;
		n.z = 0.0;
	}
	else if (maxy < maxDir + tollerance && maxy > maxDir - tollerance) {
		n.x = 0.0;
		n.z = 0.0;
	}
	else {
		n.x = 0.0;
		n.y = 0.0;
	}
	n.normalise();
	return n;
}

Cube::Cube(Vector position, float size, Colour colour)
{
	Vector corner1(position.x + size, position.y + size, position.z + size);
	Vector corner2(position.x - size, position.y - size, position.z - size);

	auto maxX = max(corner1.x, corner2.x);
	auto maxY = max(corner1.y, corner2.y);
	auto maxZ = max(corner1.z, corner2.z);
	maxVector = Vector(maxX, maxY, maxZ);
	auto minX = min(corner1.x, corner2.x);
	auto minY = min(corner1.y, corner2.y);
	auto minZ = min(corner1.z, corner2.z);
	minVector = Vector(minX, minY, minZ);
	center = (maxVector + minVector) / 2;
	color = colour;
}