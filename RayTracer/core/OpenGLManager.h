#pragma once

#include <GL/freeglut.h>
#include "RayTracer.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define WINDOW_XPOS 20
#define WINDOW_YPOS 20
#define WINDOW_TITLE "Ray Tracer"

class OpenGLManager
{
public:
	static void run(int argc, char** argv);
	static void retraceRequired();

private:
	static bool retrace;
	static RayTracer* windowRayTracer;

	static void windowDisplayCallback();
	static void windowReshapeCallback(GLint, GLint);
	static void specialKeypressCallback(int, int, int);
	static void mouseClickCallback(int, int, int, int);
	static void keypressCallback(unsigned char, int, int);
};

