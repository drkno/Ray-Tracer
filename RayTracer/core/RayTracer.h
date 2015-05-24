#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "../objects/Object.h"
#include "../objects/Sphere.h"
#include "../objects/Plane.h"
#include "../types/Color.h"
#include "../types/Vector.h"
#include "../types/PointBundle.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer();
	
	void display();
	void special(int, int, int);
	void key(unsigned char, int, int);

private:
	PointBundle closestPt(Vector pos, Vector dir);
	Color trace(Vector pos, Vector dir, int step);
};

