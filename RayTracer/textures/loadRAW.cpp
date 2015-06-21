#include "loadRAW.h"

float* loadRAW(std::string filename, int width, int height)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file)
	{
		exit(1);
	}

	auto size = width * height * 3;  //Total number of bytes to be read
	auto imageData = new char[size];
	file.read(imageData, size);
	auto colourData = new float[size];
	for (auto i = 0; i < size; i++)
	{
		colourData[i] = static_cast<unsigned char>(imageData[i]) / 255.0;
	}
	delete imageData;
	return colourData;
}