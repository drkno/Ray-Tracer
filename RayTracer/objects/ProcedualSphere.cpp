#include "ProcedualSphere.h"

ProcedualSphere::ProcedualSphere(Vector c, float r)
	: TexturedSphere(c, r, TEX_WIDTH, TEX_HEIGHT)
{
	texture = generateTexture();
};

Colour* ProcedualSphere::generateTexture()
{
	Colour* texture = new Colour[TEX_HEIGHT * TEX_WIDTH];
	int yDivisionWidth = TEX_WIDTH / HZ_DIVISIONS;
	int xDivisionWidth = TEX_HEIGHT / VZ_DIVISIONS;
	int stripeHeight = TEX_HEIGHT / 2;
	for (int x = 0; x < TEX_HEIGHT; x++)
	{
		int y1 = TEX_WIDTH * x;
		for (int y = 0; y < TEX_WIDTH; y++)
		{
			int i = y + y1;
			
			int colX = (y / xDivisionWidth) % 3;
			switch (colX)
			{
			case 0: texture[i] = Colour::RED; break;
			case 1:
			{
				int colY = (x / yDivisionWidth) % 2;
				texture[i] = Colour(colX == 1 ? colY : 1 - colY, 0, 0);
				break;
			}
			case 2: texture[i] = Colour::BLACK; break;
			}
		}
	}
	return texture;
}