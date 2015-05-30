#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "AntiAliasManager.h"

#include "../objects/Object.h"
#include "../objects/Sphere.h"
#include "../objects/Plane.h"
#include "../objects/Cube.h"
#include "../objects/ChequeredFloor.h"

#include "../types/Colour.h"
#include "../types/Vector.h"
#include "../types/PointBundle.h"

using namespace std;

class RayTracer
{
public:
	// Constructors and Deconstructors
	RayTracer();
	~RayTracer();
	
	// Public Methods
	void display();
	void special(int, int, int);
	void key(unsigned char, int, int);
	Colour trace(Vector pos, Vector dir, int step);

private:
	// Private Constant Variables
	const float WIDTH = 20.0;
	const float HEIGHT = 20.0;
	const float EDIST = 40.0;
	const int PPU = 30;     //Total 600x600 pixels
	const int MAX_STEPS = 5;
	const float XMIN = -WIDTH * 0.5;
	const float XMAX = WIDTH * 0.5;
	const float YMIN = -HEIGHT * 0.5;
	const float YMAX = HEIGHT * 0.5;

	// Private Instance Variables
	vector<Object*> sceneObjects;
	Vector light = Vector(10.0, 40.0, -5.0);
	Colour backgroundCol = Colour::GRAY;
	AntiAliasType type = AntiAliasType::None;
	float pixelSize = 1.0 / PPU;
	Vector eye = Vector(0., 0., 0.);
	float halfPixelSize = pixelSize / 2.0;
	float samplingLevel = 2;
	float halfSupersamplePixelSize = (pixelSize / samplingLevel) / 2.0;

	// Private Methods
	PointBundle closestPt(Vector pos, Vector dir);
	void drawPixel(float x, float y);
	Colour getColourSupersample(float *x, float *y);
	Colour getColourNone(float *x, float *y, float *halfSize);
	void outputPixel(Colour *col, float *x, float *y);
};

