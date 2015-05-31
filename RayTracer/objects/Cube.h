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
	Vector minVector;
	Vector maxVector;
	Vector center;

public:
	Cube(Vector, float, Colour);
	~Cube(){};

	float intersect(Vector, Vector) override;
	Vector normal(Vector) override;
};
