#pragma once

#include "Plane.h"

#define GRIDX 113
#define GRIDZ 113

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

