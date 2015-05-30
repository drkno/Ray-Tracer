#pragma once

#include "Object.h"

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class Sphere : public Object
{
private:
    Vector center;
    float radius;

public:
	Sphere();
	Sphere(Vector c, float r, Colour col);
	float intersect(Vector pos, Vector dir) override;
	Vector normal(Vector p) override;
};