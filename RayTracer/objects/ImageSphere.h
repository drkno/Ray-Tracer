#pragma once

#include "TexturedSphere.h"
#include "../textures/loadRAW.h"

class ImageSphere : public TexturedSphere
{
public:
	ImageSphere(Vector pos, float radius, std::string texture, int width, int height);
	bool isRefractive() override;
	bool isReflective() override;
};

