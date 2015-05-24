#include "RayTracer.h"

/*
* This function compares the given ray with all objects in the scene
* and computes the closest point  of intersection.
*/
PointBundle RayTracer::closestPt(Vector pos, Vector dir)
{
	Vector  point(0, 0, 0);
	float min = 10000.0;

	PointBundle out = { point, -1, 0.0 };

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		float t = sceneObjects[i]->intersect(pos, dir);
		if (t > 0)        //Intersects the object
		{
			point = pos + dir*t;
			if (t < min)
			{
				out.point = point;
				out.index = i;
				out.dist = t;
				min = t;
			}
		}
	}

	return out;
}

/*
* Computes the colour value obtained by tracing a ray.
* If reflections and refractions are to be included, then secondary rays will
* have to be traced from the point, by converting this method to a recursive
* procedure.
*/
Colour RayTracer::trace(Vector pos, Vector dir, int step)
{
	PointBundle q = closestPt(pos, dir);

	if (q.index == -1) return backgroundCol;        //no intersection

	Vector n = sceneObjects[q.index]->normal(q.point);
	Vector l = light - q.point;
	l.normalise();
	float lDotn = l.dot(n); //Note ‘l’ is the letter el, not the number 1.

	Colour col = sceneObjects[q.index]->getColour(q.point); //Object's colour

	Vector lightVector = light - q.point;
	float lightDist = lightVector.length(); //Distance to light
	lightVector.normalise();
	PointBundle s = closestPt(q.point, lightVector);

	if (s.index > -1 && s.dist < lightDist)
	{
		return col.phongLight(backgroundCol, 0.0, 0.0);
	}
	if (lDotn <= 0)
	{
		return col.phongLight(backgroundCol, 0.0, 0.0);
	}

	Vector r = ((n * 2) * lDotn) - l; // r = 2(L.n)n – L. ‘l’ = el
	r.normalise();
	Vector v(-dir.x, -dir.y, -dir.z); //View vector;
	float rDotv = r.dot(v);
	float spec = rDotv < 0 ? 0.0 : pow(rDotv, 10); //Phong exponent = 10

	Colour colorSum = col.phongLight(backgroundCol, lDotn, spec);

	// generate reflection array
	if (q.index == 0 && step < MAX_STEPS)
	{
		float reflCoeff = 0.65;
		Vector reflectionVector = ((n * 2)*(n.dot(v))) - v;
		Colour reflectionColor = trace(q.point, reflectionVector, step + 1);
		colorSum.combineColor(reflectionColor, reflCoeff);
	}

	return colorSum;
}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each pixel as quads.
//---------------------------------------------------------------------------------------
void RayTracer::display()
{
	int widthInPixels = (int)(WIDTH * PPU);
	int heightInPixels = (int)(HEIGHT * PPU);
	float pixelSize = 1.0 / PPU;
	float halfPixelSize = pixelSize / 2.0;
	float x1, y1, xc, yc;
	Vector eye(0., 0., 0.);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);  //Each pixel is a quad.

	for (int i = 0; i < widthInPixels; i++)	//Scan every "pixel"
	{
		x1 = XMIN + i*pixelSize;
		xc = x1 + halfPixelSize;
		for (int j = 0; j < heightInPixels; j++)
		{
			y1 = YMIN + j*pixelSize;
			yc = y1 + halfPixelSize;

			Vector dir(xc, yc, -EDIST);	//direction of the primary ray

			dir.normalise();			//Normalise this direction

			Colour col = trace(eye, dir, 1); //Trace the primary ray and get the colour value
			glColor3f(col.r, col.g, col.b);
			glVertex2f(x1, y1);				//Draw each pixel with its color value
			glVertex2f(x1 + pixelSize, y1);
			glVertex2f(x1 + pixelSize, y1 + pixelSize);
			glVertex2f(x1, y1 + pixelSize);
		}
	}

	glEnd();
	glFlush();
}

RayTracer::RayTracer()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);

	Sphere *sphere1 = new Sphere(Vector(5, 6, -70), 3.0, Colour::RED);
	Sphere *sphere2 = new Sphere(Vector(-5, -6, -80), 10.0, Colour::BLUE);
	Sphere *sphere3 = new Sphere(Vector(12, 12, -70), 4.0, Colour::GREEN);
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);

	Cube *cube = new Cube(Vector(9, -3, -60), Vector(12, -6, -70), Colour::GREEN);
	sceneObjects.push_back(cube);

	Plane *plane = new Plane(Vector(-40, -10, -40), Vector(40, -10, -40),
		Vector(40, -10, -150), Vector(-40, -10, -150), Colour(1, 0, 1), Colour(0.001, 0, 0));
	sceneObjects.push_back(plane);
}

RayTracer::~RayTracer()
{
	while (!sceneObjects.empty())
	{
		auto object = sceneObjects.back();
		sceneObjects.pop_back();
		delete object;
	}
}

void RayTracer::special(int, int, int)
{
	
}
void RayTracer::key(unsigned char, int, int)
{
	
}