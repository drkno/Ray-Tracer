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
	ChequeredFloor(Vector, Vector, Vector, Vector, Colour, Colour);
};

