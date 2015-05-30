#include "ImageSphere.h"

ImageSphere::ImageSphere(Vector pos, float radius, std::string texture, int width, int height)
	: TexturedSphere(pos, radius, width, height)
{
	this->texture = loadRAW(texture, width, height);
}

bool ImageSphere::isRefractive()
{
	return false;
}

bool ImageSphere::isReflective()
{
	return false;
}
