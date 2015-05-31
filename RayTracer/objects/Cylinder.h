#pragma once

#include <algorithm>
#include "Object.h"

using namespace std;

class Cylinder : public Object
{
public:
	float intersect(Vector pos, Vector dir) override;
	Vector normal(Vector pos) override;
	Cylinder(Vector,float,float,Colour);

private:
	float radius;
	float height;
	float heightMax;
	float heightMin;
	Vector center;
};

