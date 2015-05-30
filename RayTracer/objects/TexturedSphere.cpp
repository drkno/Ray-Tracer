#include "TexturedSphere.h"

TexturedSphere::TexturedSphere(Vector c, float r, int width, int height)
	: Sphere(c, r, Colour::BLACK)
{
	center = c;
	radius = r;
	color = Colour::WHITE;
	this->width = width;
	this->height = height;
	this->texture = NULL;
};

TexturedSphere::~TexturedSphere()
{
	delete texture;
}

Colour TexturedSphere::getColour(Vector pos)
{
	int yCoord = static_cast<int>(((pos.y - center.y + radius) / (radius * 2.0)) * height);

	pos.x -= center.x;
	pos.z -= center.z;

	float angle = (pos.z / pos.x);
	angle = angle < 0 ? -1 * angle : angle;
	angle = atanf(angle);

	if (pos.z >= 0)
	{
		if (pos.x < 0)
		{
			angle = PI - angle;
		}
	}
	else
	{
		angle = pos.x < 0 ? angle + PI : 2.0f * PI - angle;
	}

	int xCoord = static_cast<int>((angle / (2.0 * PI)) * width);
	int index = (xCoord + (yCoord * width)) * 3;

	return Colour(texture[index], texture[index + 1], texture[index + 2]);
}