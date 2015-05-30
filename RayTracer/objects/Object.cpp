/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The object class
*  This is a generic type for storing objects in the scene
*  Sphere, Plane etc. must be defined as subclasses of Object.
*  Being an abstract class, this class cannot be instantiated.
-------------------------------------------------------------*/

#include "Object.h"

Colour Object::getColour()
{
	return color;
}


Colour Object::getColour(Vector)
{
	return color;
}

void Object::setColor(Colour col)
{
	color = col;
}

float Object::getRefractiveIndex()
{
	return refractiveIndex;
}


void Object::setRefractiveIndex(float index)
{
	refractiveIndex = index;
}

bool Object::isRefractive()
{
	return refractiveIndex > 0;
}

float Object::getReflectiveness()
{
	return reflectiveness;
}

void Object::setReflectiveness(float reflectiveness)
{
	this->reflectiveness = reflectiveness;
}

bool Object::isReflective()
{
	return reflectiveness > 0;
}