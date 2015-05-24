#pragma once

#include <math.h>
#include <algorithm>
#include "Object.h"
#include "../types/Colour.h"

using namespace std;

/**
* Defines a simple Cube located at 'center'
* with the specified diameter
*/
class Cube : public Object
{
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	//Vector firstCorner, secondCorner;

public:
	Cube(Vector, Vector, Colour);
	~Cube(){};

	float intersect(Vector, Vector);
	Vector normal(Vector);
};
