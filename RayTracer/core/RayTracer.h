#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#if defined(_MSC_VER) && _MSC_VER >= 1700 || defined(__cplusplus) && __cplusplus > 199711L
#define CPP11 1
#include <thread>
#include <chrono>
#endif

#include "AntiAliasManager.h"
#include "PixelStore.h"

#include "../objects/Object.h"
#include "../objects/Sphere.h"
#include "../objects/Plane.h"
#include "../objects/Cube.h"
#include "../objects/ChequeredFloor.h"
#include "../objects/ProcedualSphere.h"
#include "../objects/ImageSphere.h"
#include "../objects/Cylinder.h"
#include "../objects/Cone.h"

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
	AntiAliasType type = Supersample;
	float pixelSize = 1.0 / PPU;
	Vector eye = Vector(0., 0., 0.);
	float halfPixelSize = pixelSize / 2.0;
	const int samplingLevel = 4;
	const int samplingSize = 16;
	const float aaPixelSize = (static_cast<float>(samplingLevel) / samplingSize) * pixelSize;
	float edist = 40.0;

	bool fogEnabled = true;
	int fogColourPos = 0;
	Colour fogColour = Colour::WHITE;
	int fogStart = 40;
	int fogEnd = 120;
	float fogMax = 0.5;
	int fogRange;

#ifdef CPP11
	unsigned int numberOfThreads = 4;
#else
	const unsigned int numberOfThreads = 0;
#endif

	// Private Methods
	PointBundle closestPt(Vector pos, Vector dir);
	Colour getColourSupersample(float *x, float *y);
	Colour getColourNone(float *x, float *y);
	void outputPixel(Colour *col, float *x, float *y);
	Colour getPixel(float *x, float *y);
	void display_thread(vector<PixelStore>&, int, int, int);
	void controlFogDepth(int*, int, string);
};

