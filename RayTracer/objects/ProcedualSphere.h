#pragma once

#include "TexturedSphere.h"

#define TEX_WIDTH 10
#define TEX_HEIGHT 12
#define HZ_DIVISIONS 10
#define VZ_DIVISIONS 12

class ProcedualSphere : public TexturedSphere
{
private:
	Colour* generateTexture();

public:	
	ProcedualSphere(Vector c, float r);
};
