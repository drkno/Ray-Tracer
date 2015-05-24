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
