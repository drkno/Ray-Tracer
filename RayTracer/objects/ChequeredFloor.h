#pragma once

#include "Plane.h"
class ChequeredFloor : public Plane
{
private:
	Colour colorB;

public:
	Colour getColour(Vector);
	ChequeredFloor(void);
	ChequeredFloor(Vector pa, Vector pb, Vector pc, Vector pd, Colour colA, Colour colB)
		: Plane(pa,pb,pc,pd,colA)
	{
		colorB = colB;
	};
};

