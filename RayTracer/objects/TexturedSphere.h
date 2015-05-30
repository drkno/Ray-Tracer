/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#pragma once

#include "Sphere.h"

#define PI 3.14159265358979323846

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class TexturedSphere : public Sphere
{

protected:
    Vector center;
    float radius;
	float* texture;
	double width;
	double height;

public:	
	TexturedSphere(Vector, float, int, int);
	~TexturedSphere();
	Colour getColour(Vector) override;
};
