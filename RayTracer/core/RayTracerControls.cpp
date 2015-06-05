#include "RayTracer.h"

void RayTracer::special(int key, int, int)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		{
			cout << "Eye Distance" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\t" << edist << endl;

			if (edist == 100) break;
			edist += 2;

			cout << "After:\t" << edist << endl << endl;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			cout << "Eye Distance" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\t" << edist << endl;

			if (edist == 0) break;
			edist -= 2;

			cout << "After:\t" << edist << endl << endl;
			glutPostRedisplay();
			break;
		}
	}
}

void RayTracer::key(unsigned char key, int, int)
{
	switch (key)
	{
		case 'A':
		case 'a':
		{
			const string aa[] = { "None", "Supersample" };
			cout << "Anti-Aliasing" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\t" << aa[type].c_str() << endl;

			type = static_cast<AntiAliasType>((type + 1) % 2);

			cout << "After:\t" << aa[type].c_str() << endl << endl;

			glutPostRedisplay();
			break;
		}
#ifdef CPP11
		case '=':
		case '+':
		{
			cout << "Threads" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\t" << numberOfThreads << endl;

			if (numberOfThreads < 20) numberOfThreads++;

			cout << "After:\t" << numberOfThreads << endl << endl;
			break;
		}
		case '-':
		case '_':
		{
			cout << "Threads" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\t" << numberOfThreads << endl;

			if (numberOfThreads > 0) numberOfThreads--;

			cout << "After:\t" << numberOfThreads << endl << endl;
			break;
		}
#endif
		case 'R':
		case 'r':
		{
			cout << "Forcing Redraw..." << endl;
			glutPostRedisplay();
			break;
		}
		case 'F':
		case 'f':
		{
			cout << "Fog" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\tFog " << (fogEnabled ? "On" : "Off") << endl;

			fogEnabled = !fogEnabled;

			cout << "After:\tFog " << (fogEnabled ? "On" : "Off") << endl << endl;
			glutPostRedisplay();
			break;
		}
		case '[':
		case '{':
		{
			controlFogDepth(&fogStart, -10, "Start");
			break;
		}
		case ']':
		case '}':
		{
			controlFogDepth(&fogStart, 10, "Start");
			break;
		}
		case ';':
		case ':':
		{
			controlFogDepth(&fogEnd, -10, "End");
			break;
		}
		case '\'':
		case '"':
		{
			controlFogDepth(&fogEnd, 10, "End");
			break;
		}
		case ',':
		case '<':
		{
			cout << "Fog" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\tFog Max Strength " << fogMax << endl;

			if (fogMax > 0) fogMax -= 0.1;

			cout << "After:\tFog Max Strength " << fogMax << endl << endl;
			if (fogEnabled) glutPostRedisplay();
			break;
		}
		case '.':
		case '>':
		{
			cout << "Fog" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\tFog Max Strength " << fogMax << endl;

			if (fogMax < 1) fogMax += 0.1;

			cout << "After:\tFog Max Strength " << fogMax << endl << endl;
			if (fogEnabled) glutPostRedisplay();
			break;
		}
		case 'Q':
		case 'q':
		{
			cout << "Quitting..." << endl;
			exit(0);
			break;
		}
		case '?':
		case '/':
		{
			const string colours[] = {"White", "Blue", "Red", "Green", "Yellow", "Magenta", "Cyan" };
			const Colour colourVals[] = { Colour::WHITE, Colour::BLUE, Colour::RED, Colour::GREEN, Colour(1, 1, 0), Colour(1, 0, 1), Colour(0, 1, 1) };

			cout << "Fog" << endl
				<< "-----------------------------------------------" << endl
				<< "Before:\tFog Colour " << colours[fogColourPos] << endl;

			fogColourPos = (fogColourPos + 1) % 7;
			fogColour = colourVals[fogColourPos];

			cout << "After:\tFog Colour " << colours[fogColourPos] << endl << endl;
			if (fogEnabled) glutPostRedisplay();
			break;
		}
	}
}

void RayTracer::controlFogDepth(int *depth, int change, string changeName)
{
	cout << "Fog" << endl
		<< "-----------------------------------------------" << endl
		<< "Before:\tFog " << changeName << " Depth " << *depth << endl;

	auto n = *depth + change;
	if (n >= 0 && n <= 150) *depth = n;

	cout << "After:\tFog " << changeName << " Depth " << *depth << endl << endl;
	if (fogEnabled) glutPostRedisplay();
}