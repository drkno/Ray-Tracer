#include "OpenGLManager.h"

RayTracer* OpenGLManager::windowRayTracer = NULL;

void OpenGLManager::run(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_XPOS, WINDOW_YPOS);
	glutCreateWindow(WINDOW_TITLE);
	windowRayTracer = new RayTracer();
	glutDisplayFunc(windowDisplayCallback);
	//glutTimerFunc(CALLBACK_RATE, displayRefreshCallback, 0);
	glutReshapeFunc(windowReshapeCallback);
	glutSpecialFunc(specialKeypressCallback);
	glutMouseFunc(mouseClickCallback);
	glutKeyboardFunc(keypressCallback);
	glutMainLoop();
	windowRayTracer->~RayTracer();
}

void OpenGLManager::windowDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	windowRayTracer->display();
	glutSwapBuffers();
}

void OpenGLManager::displayRefreshCallback(int value)
{
	glutPostRedisplay();
	glutTimerFunc(CALLBACK_RATE, displayRefreshCallback, ++value);
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

