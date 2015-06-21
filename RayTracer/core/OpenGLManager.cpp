#include "OpenGLManager.h"

bool OpenGLManager::retrace = true;
RayTracer* OpenGLManager::windowRayTracer = NULL;

void OpenGLManager::run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_XPOS, WINDOW_YPOS);
	glutCreateWindow(WINDOW_TITLE);
	retrace = true;
	windowRayTracer = new RayTracer();
	glutReshapeFunc(windowReshapeCallback);
	glutSpecialFunc(specialKeypressCallback);
	glutMouseFunc(mouseClickCallback);
	glutKeyboardFunc(keypressCallback);
	glutDisplayFunc(windowDisplayCallback);
	glutMainLoop();
	windowRayTracer->~RayTracer();
	delete windowRayTracer;
}

void OpenGLManager::retraceRequired()
{
	retrace = true;
	glutPostRedisplay();
}

void OpenGLManager::windowDisplayCallback()
{
	if (!retrace) return;
	retrace = false;
	windowRayTracer->display();
}

void OpenGLManager::windowReshapeCallback(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void OpenGLManager::specialKeypressCallback(int key, int x, int y)
{
	windowRayTracer->special(key, x, y);
	if (key == GLUT_KEY_F12)
	{
		glutFullScreenToggle();
	}
}

void OpenGLManager::keypressCallback(unsigned char key, int x, int y)
{
	windowRayTracer->key(key, x, y);
}

void OpenGLManager::mouseClickCallback(int button, int state, int x, int y)
{
	if (state == GLUT_UP) windowRayTracer->special(-1, x, y);
}

