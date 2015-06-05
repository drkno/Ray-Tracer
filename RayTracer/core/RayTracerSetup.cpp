#include "RayTracer.h"

RayTracer::RayTracer()
{
	fogRange = fogEnd - fogStart;

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);

	auto plane = new ChequeredFloor(Vector(-300, -10, 300), Vector(300, -10, 300),
		Vector(300, -10, -150), Vector(-300, -10, -150), Colour::WHITE, Colour::BLACK);
	sceneObjects.push_back(plane);

	auto cone = new Cone(Vector(-10, -10, -60), 7, 2, Colour::GREEN);
	sceneObjects.push_back(cone);

	auto cylinder = new Cylinder(Vector(10, -6.5, -60), 7, 2, Colour::RED);
	sceneObjects.push_back(cylinder);

	auto moon = new ImageSphere(Vector(10, 0, -60), 4, "Moon.raw", 256, 128);
	sceneObjects.push_back(moon);

	auto earth = new ImageSphere(Vector(-10, 0, -60), 4, "Earth.raw", 256, 128);
	sceneObjects.push_back(earth);

	auto box = new Cube(Vector(4, -8, -40), 1.5, Colour::GREEN);
	sceneObjects.push_back(box);

	auto texturedSphere = new ProcedualSphere(Vector(-4, -8, -40), 2);
	sceneObjects.push_back(texturedSphere);

	auto refractiveSphere = new Sphere(Vector(0, -5, -50), 3, Colour::BLACK);
	refractiveSphere->setRefractiveIndex(1.3333);
	sceneObjects.push_back(refractiveSphere);

	auto transparentSphere = new Sphere(Vector(-10, -7.5, -80), 2.5, Colour::WHITE);
	transparentSphere->setRefractiveIndex(1);
	sceneObjects.push_back(transparentSphere);

	auto sphere = new Sphere(Vector(10, -7.5, -80), 2.5, Colour::BLACK);
	sceneObjects.push_back(sphere);

	auto reflectiveSphere = new Sphere(Vector(0, 0, -90), 10, Colour::BLUE);
	reflectiveSphere->setReflectiveness(0.6);
	sceneObjects.push_back(reflectiveSphere);

	auto boundryCube1 = new Cube(Vector(-33, 5, -80), 15, Colour(0.5, 0, 0));
	sceneObjects.push_back(boundryCube1);

	auto boundryCube2 = new Cube(Vector(33, 5, -80), 15, Colour::BLUE);
	sceneObjects.push_back(boundryCube2);
}