#pragma once

#include "../types/Vector.h"
#include "Object.h"
#include <math.h>

#define GRIDX 113
#define GRIDZ 113

class ChequeredFloor : public Object
{
private:
	Vector a, b, c, d;      //The 4 vertices of a quad
	Colour colorB;

public:
	Colour getColour(Vector) override;
	ChequeredFloor(Vector, Vector, Vector, Vector, Colour, Colour);
	bool isInside(Vector);
	float intersect(Vector, Vector) override;
	Vector normal(Vector) override;
};

