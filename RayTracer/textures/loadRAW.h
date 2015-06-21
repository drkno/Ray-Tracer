//======================================================================
// LoadRAW.h
// Image loader for files in RAW format.
// Assumption:  Colour image in RGB format (24 bpp) in interleaved order.
// Note: RAW format stores an image in top to bottom order, and will
//       appear vertically flipped.
// Author:
// R. Mukundan, Department of Computer Science and Software Engineering
// University of Canterbury, Christchurch, New Zealand.
//
// Modified to return useful values by:
// M. Knox, Knox Enterprises, NZ
//======================================================================

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "../types/Colour.h"

using namespace std;

Colour* loadRAW(string filename, int width, int height);
