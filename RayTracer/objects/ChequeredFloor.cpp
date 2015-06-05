#include "ChequeredFloor.h"

ChequeredFloor::ChequeredFloor(Vector pa, Vector pb, Vector pc, Vector pd, Colour colA, Colour colB)
	: Plane(pa, pb, pc, pd, colA)
{
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
