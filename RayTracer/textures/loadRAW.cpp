#include "loadRAW.h"

Colour* loadRAW(string filename, int width, int height)
{
	ifstream file(filename.c_str(), ios::in | ios::binary);
	if (!file)
	{
		cerr << "---------- ERROR ----------" << endl;
		cerr << "A texture file was missing: \"" << filename << "\"" << endl;
		cerr << "Please ensure that this file is placed in the appropriate" << endl
			 << "working directory before retrying to use this application." << endl;
		cerr << endl << "Critical Error, quitting..." << endl;
		exit(1);
	}

	auto size = width * height;  //Total number of bytes to be read
	auto bSize = size * 3;
	auto imageData = new char[bSize];
	file.read(imageData, bSize);
	auto colourData = new Colour[size];
	for (auto i = 0; i < size; i++)
	{
		auto c = i * 3;
		colourData[i] = Colour(
			static_cast<unsigned char>(imageData[c]) / 255.0,
			static_cast<unsigned char>(imageData[c + 1]) / 255.0,
			static_cast<unsigned char>(imageData[c + 2]) / 255.0);
	}
	delete imageData;
	return colourData;
}