#pragma once

#include <algorithm>
#include "Object.h"

using namespace std;

class Cone : public Object
{
private:
	float intersect(Vector pos, Vector dir) override;
	Vector normal(Vector pos) override;

	Vector center;
	float height;
	float radius;

public:
	Cone(Vector,float,float,Colour);
};

