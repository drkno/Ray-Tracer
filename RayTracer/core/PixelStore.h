#pragma once
#include "../types/Colour.h"

class PixelStore
{
public:
	Colour colour;
	float x;
	float y;

	PixelStore(Colour colour, float x, float y)
	{
		this->colour = colour;
		this->x = x;
		this->y = y;
	}
};