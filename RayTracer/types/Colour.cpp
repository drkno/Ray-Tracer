/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The color class
*  A simple colour class with a set of operations including
*    phong lighting.
-------------------------------------------------------------*/
#include "Colour.h"

//Multiplies the current colour by a scalar factor
void Colour::scaleColor(float scaleFactor) 
{
    r = r * scaleFactor;
    g = g * scaleFactor;
    b = b * scaleFactor;
}

//Modulates the current colour by a given colour
void Colour::combineColor(Colour col)
{
    r *= col.r;
    g *= col.g;
    b *= col.b;
}

//Adds a scaled version of a colour to the current colour
void Colour::combineColor(Colour col, float scaleFactor)
{
    r +=  scaleFactor * col.r;
    g +=  scaleFactor * col.g;
    b +=  scaleFactor * col.b;
}

//Phong lighting equations:
// Input:  Light's ambient color, l.n,  (r.v)^f
// Assumptions:
//   Material ambient = Material diffuse = current color
//   Material specular = white
//   Light diffuse = Light specular = white

Colour Colour::phongLight(Colour ambientCol, float diffTerm, float specTerm)
{
	Colour col;
    col.r = (ambientCol.r) * r + diffTerm * r + specTerm;
    col.g = (ambientCol.g) * g + diffTerm * g + specTerm;
    col.b = (ambientCol.b) * b + diffTerm * b + specTerm;
	return col;
}

const Colour& Colour::operator+=(Colour other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}

const Colour& Colour::operator/=(int scale)
{
	r /= scale;
	g /= scale;
	b /= scale;
	return *this;
}

Colour Colour::average(std::vector<Colour> colours)
{
	Colour col;
	col.r = this->r;
	col.g = this->g;
	col.b = this->b;
	for (int i = 0; i < colours.size(); i++)
	{
		col.r += colours[i].r;
		col.g += colours[i].g;
		col.b += colours[i].b;
	}
	int size = colours.size();
	col.r /= size;
	col.g /= size;
	col.b /= size;
	return col;
}

const Colour Colour::WHITE = Colour(1, 1, 1);
const Colour Colour::BLACK = Colour(0, 0, 0);
const Colour Colour::RED = Colour(1, 0, 0);
const Colour Colour::GREEN = Colour(0, 1, 0);
const Colour Colour::BLUE = Colour(0, 0, 1);
const Colour Colour::GRAY = Colour(0.2f, 0.2f, 0.2f);