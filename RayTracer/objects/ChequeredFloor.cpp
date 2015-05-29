#include "ChequeredFloor.h"

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