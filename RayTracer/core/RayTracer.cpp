#include "RayTracer.h"

/*
* This function compares the given ray with all objects in the scene
* and computes the closest point  of intersection.
*/
PointBundle RayTracer::closestPt(Vector pos, Vector dir)
{
	Vector point(0, 0, 0);
	float min = 10000.0;

	PointBundle out = {point, -1, 0.0};

	for (auto i = 0; i < sceneObjects.size(); i++)
	{
		auto t = sceneObjects[i]->intersect(pos, dir);
		if (t > 0) //Intersects the object
		{
			point = pos + dir * t;
			if (t < min)
			{
				out.point = point;
				out.index = i;
				out.dist = t;
				min = t;
			}
		}
	}

	return out;
}

/*
* Computes the colour value obtained by tracing a ray.
* If reflections and refractions are to be included, then secondary rays will
* have to be traced from the point, by converting this method to a recursive
* procedure.
*/
Colour RayTracer::trace(Vector pos, Vector dir, int step)
{
	auto q = closestPt(pos, dir);

	/*float fogAmount = fogProgression * (q.dist - fogStart);
	Colour background = backgroundCol;
	backgroundCol.combineColor(fogColourfogProgression);*/

	if (q.index == -1) return backgroundCol; //no intersection

	auto n = sceneObjects[q.index]->normal(q.point);
	auto l = light - q.point;
	l.normalise();
	float lDotn = l.dot(n); //Note ‘l’ is the letter el, not the number 1.

	Colour col = sceneObjects[q.index]->getColour(q.point); //Object's colour

	Vector lightVector = light - q.point;
	float lightDist = lightVector.length(); //Distance to light
	lightVector.normalise();
	PointBundle s = closestPt(q.point, lightVector);

	Vector v(-dir.x, -dir.y, -dir.z); //View vector;

	Colour colourSum;
	float spec = 0.0f;

	if (s.index > -1 && s.dist < lightDist || lDotn <= 0)
	{
		colourSum = col.phongLight(backgroundCol, 0.0, 0.0);
		if (!sceneObjects[q.index]->isReflective() &&
			!sceneObjects[q.index]->isRefractive())
		{
			return colourSum;
		}
	}
	else
	{
		Vector r = ((n * 2) * lDotn) - l; // r = 2(L.n)n – L. ‘l’ = el
		r.normalise();
		float rDotv = r.dot(v);
		spec = rDotv < 0 ? 0.0 : pow(rDotv, 10); //Phong exponent = 10
		colourSum = col.phongLight(backgroundCol, lDotn, spec);
	}

	bool shouldReflect = false;
	if (sceneObjects[q.index]->isRefractive() && step < MAX_STEPS)
	{
		Vector d = dir, nor = n;
		float n1 = 1.0, n2 = sceneObjects[q.index]->getRefractiveIndex();
		float r = n1 / n2;

		float e = 1 - powf(r, 2) * (1 - powf(dir.dot(n), 2));
		float t = sqrtf(e);

		Vector g = d * r - nor * (r * (dir.dot(n)) + t);

		PointBundle b = closestPt(q.point, g);
		nor = sceneObjects[q.index]->normal(b.point);
		nor *= -1;
		r = n2 / n1;
		e = 1 - powf(r, 2) * (1 - powf(g.dot(nor), 2));
		t = sqrtf(e);
		g = g * r - nor * (r * (g.dot(nor)) + t);

		Colour refractColour = trace(b.point, g, step + 1);
		if (sceneObjects[q.index]->getReflectiveness() == 1)
		{
			colourSum = refractColour.phongLight(backgroundCol, lDotn, spec);
		}
		else
		{
			colourSum.combineColor(refractColour, 1 / n2);
		}
		return colourSum;
	}

	// generate reflection ray
	if (shouldReflect || sceneObjects[q.index]->isReflective() && step < MAX_STEPS)
	{
		float reflCoeff = shouldReflect ? 1 : sceneObjects[q.index]->getReflectiveness();
		Vector reflectionVector = ((n * 2) * (n.dot(v))) - v;
		Colour reflectionColor = trace(q.point, reflectionVector, step + 1);
		if (reflCoeff == 1)
		{
			colourSum = reflectionColor.phongLight(backgroundCol, lDotn, spec);
		}
		else
		{
			colourSum.combineColor(reflectionColor, reflCoeff);
		}
	}

	return colourSum;
}

void RayTracer::display()
{
	cout << "Redraw Initiated" << endl << "-----------------------------------------------" << endl << "Ray-tracing...";
#ifdef CPP11
	auto before = chrono::high_resolution_clock::now();
#endif

	int widthInPixels = WIDTH * PPU;
	int heightInPixels = HEIGHT * PPU;

	auto out = new vector<PixelStore>[numberOfThreads + 1];
#ifdef CPP11
	vector<thread> threads;
	for (auto i = 1; i <= numberOfThreads; i++)
	{
		threads.push_back(thread(&RayTracer::display_thread, this, ref(out[i]), i, widthInPixels, heightInPixels));
	}
#endif
	display_thread(out[0], 0, widthInPixels, heightInPixels);

	cout << "\t\tComplete." << endl << "Drawing pixels...";

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	for (auto i = 0; i < numberOfThreads + 1; i++)
	{
#ifdef CPP11
		if (i > 0 && threads[i - 1].joinable()) threads[i - 1].join();
#endif
		for (auto j = 0; j < out[i].size(); j++)
		{
			auto store = &out[i][j];
			outputPixel(&store->colour, &store->x, &store->y);
		}
	}
	glEnd();
	glFlush();

	delete[]out;

	cout << "\tComplete." << endl;
#ifdef CPP11
	auto after = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(after - before).count();
	cout << "Completed in " << duration << "ms." << endl << endl;
#else
	cout << "Complete." << endl << endl;
#endif
}

void RayTracer::display_thread(vector<PixelStore> &out, int threadNum, int widthInPixels, int heightInPixels)
{
	auto doneCount = (widthInPixels / 100) * (threadNum + 1) + threadNum;
	float x1, y1;

	for (auto i = threadNum; i < widthInPixels; i += (numberOfThreads + 1))
	{
		x1 = XMIN + i * pixelSize;
		for (auto j = 0; j < heightInPixels; j++)
		{
			y1 = YMIN + j * pixelSize;
			auto colour = getPixel(&x1, &y1);
			PixelStore store(colour, x1, y1);
			out.push_back(store);
		}
	}
}

Colour RayTracer::getPixel(float *x, float *y)
{
	Colour colour;
	switch (type)
	{
	default:
	case None:
	{
		colour = getColourNone(x, y, &halfPixelSize);
		break;
	}
	case Supersample: colour = getColourSupersample(x, y); break;
	}

	return colour;
}

void RayTracer::outputPixel(Colour *col, float *x, float *y)
{
	glColor3f(col->r, col->g, col->b);
	glVertex2f(*x, *y); //Draw each pixel with its color value
	glVertex2f(*x + pixelSize, *y);
	glVertex2f(*x + pixelSize, *y + pixelSize);
	glVertex2f(*x, *y + pixelSize);
}

Colour RayTracer::getColourNone(float *x, float *y, float *halfSize)
{
	float xc = *x + *halfSize;
	float yc = *y + *halfSize;
	Vector dir(xc, yc, -edist); //direction of the primary ray
	dir.normalise(); //Normalise this direction
	return trace(eye, dir, 1); //Trace the primary ray and get the colour value
}

Colour RayTracer::getColourSupersample(float *x, float *y)
{
	Colour average(0, 0, 0);
	float frag_x = *x, frag_y;
	for (auto i = 0; i < samplingLevel; i++)
	{
		frag_y = *y;
		for (auto j = 0; j < samplingLevel; j++)
		{
			Vector direction(frag_x, frag_y, -edist);
			direction.normalise();
			average += trace(eye, direction, 1);
			frag_y += aaPixelSize;
		}
		frag_x += aaPixelSize;
	}
	average /= samplingSize;
	return average;
}

RayTracer::RayTracer()
{
	fogProgression = 0.5 / (fogEnd - fogStart);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);

	Sphere* sphere1 = new Sphere(Vector(0, 0, -40), 4.0, Colour::RED);
	//sphere1->setRefractiveIndex(1.1);
	//sphere1->setReflectiveness(1);
	//sceneObjects.push_back(sphere1);
	/*Sphere* sphere2 = new Sphere(Vector(-10, 6, -100), 4.0, Colour::GREEN);
	sphere2->setReflectiveness(1);
	Sphere* sphere3 = new Sphere(Vector(5, 0, -100), 10.0, Colour::BLUE);
	sphere3->setReflectiveness(0.65);

	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);

	

	Cube* cube = new Cube(Vector(10, -7, -80), 2.5, Colour::GREEN);
	sceneObjects.push_back(cube);*/

	auto plane = new ChequeredFloor(Vector(-300, -10, 300), Vector(300, -10, 300),
	                         Vector(300, -10, -150), Vector(-300, -10, -150), Colour::WHITE, Colour::BLACK);
	sceneObjects.push_back(plane);

	//ProcedualSphere *procedual = new ProcedualSphere(Vector(-10, 0, -80), 2.5);
	//sceneObjects.push_back(procedual);

	//ImageSphere *imageSphere = new ImageSphere(Vector(0, 0, -50), 5.0, "Moon.raw", 256, 128);
	//sceneObjects.push_back(imageSphere);

	//Cylinder *cylinder = new Cylinder(Vector(0, -5, -50), 3, 2.5, Colour::RED);
	//sceneObjects.push_back(cylinder);

	//Cone *cone = new Cone(Vector(0, 0, -30), 6, 3, Colour::GREEN);
	//sceneObjects.push_back(cone);

}

RayTracer::~RayTracer()
{
	while (!sceneObjects.empty())
	{
		auto object = sceneObjects.back();
		sceneObjects.pop_back();
		delete object;
	}
}

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
			string aa[] = {"None", "Supersample"};
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
		case 'Q':
		case 'q':
		{
			cout << "Quitting..." << endl;
			exit(0);
			break;
		}
	}
}
