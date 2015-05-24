#include "OpenGLManager.h"

// Main entry point for the application
int main(int argc, char* argv[]) {
	// Start the GUI.
	// Note: this should never, ever, ever be called multiple times...
	OpenGLManager::run(argc, argv);
	return 0;
}