#include "OpenGLManager.h"

// Main entry point for the application
int main(int argc, char* argv[]) {
	cout << "RAY TRACER" << endl
		<< "---------------------------" << endl
		<< "Author:\t\tMatthew Knox <mrk45@uclive.ac.nz>" << endl
		<< "Last Edited:\t05/06/15" << endl
		<< "Student Info:\tmrk45, 81118603" << endl << endl
		<< "This program except where code is sourced from elsewhere is " << endl
		<< "licensed under the MIT license. Origional source code will be " << endl
		<< "avalible AFTER marking is complete from here:" << endl
		<< "https://github.com/mrkno/Ray-Tracer" << endl << endl;

	// Start the GUI.
	// Note: this should never, ever, ever be called multiple times...
	OpenGLManager::run(argc, argv);
	return 0;
}