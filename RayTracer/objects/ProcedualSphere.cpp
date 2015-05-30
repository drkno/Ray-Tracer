#include "ProcedualSphere.h"

ProcedualSphere::ProcedualSphere(Vector c, float r)
	: TexturedSphere(c, r, TEX_WIDTH, TEX_HEIGHT)
{
	texture = generateTexture();
};

float* ProcedualSphere::generateTexture()
{
	float* texture = new float[TEX_HEIGHT * TEX_WIDTH * 3];
	int yDivisionWidth = TEX_WIDTH / HZ_DIVISIONS;
	int xDivisionWidth = TEX_HEIGHT / VZ_DIVISIONS;
	int stripeHeight = TEX_HEIGHT / 2;
	for (int x = 0; x < TEX_HEIGHT; x++)
	{
		int y1 = TEX_WIDTH * 3 * x;
		for (int y = 0; y < TEX_WIDTH; y++)
		{
			int i = y * 3 + y1;
			
			int colX = (y / xDivisionWidth) % 3;
			switch (colX)
			{
			case 0: texture[i] = 1; break;
			case 1:
			{
				int colY = (x / yDivisionWidth) % 2;
				texture[i] = colX == 1 ? colY : 1 - colY;
				break;
			}
			case 2: texture[i] = 0; break;
			}
			texture[i + 1] = 0;
			texture[i + 2] = 0;
		}
	}
	return texture;
}