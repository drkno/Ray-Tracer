CC = g++
CFLAGS = -L/usr/lib/nvidia-331 -lm -lGL -lGLU -lglut -std=c++11
OUTNAME = Ray-Tracer

all:
	$(CC) -o $(OUTNAME) ./RayTracer/core/main.cpp ./RayTracer/core/OpenGLManager.cpp ./RayTracer/core/RayTracer.cpp ./RayTracer/core/RayTracerControls.cpp ./RayTracer/objects/ChequeredFloor.cpp ./RayTracer/objects/Cone.cpp ./RayTracer/objects/Cube.cpp ./RayTracer/objects/Cylinder.cpp ./RayTracer/objects/ImageSphere.cpp ./RayTracer/objects/Object.cpp ./RayTracer/objects/ProcedualSphere.cpp ./RayTracer/objects/Sphere.cpp ./RayTracer/objects/TexturedSphere.cpp ./RayTracer/textures/loadRAW.cpp ./RayTracer/types/Colour.cpp ./RayTracer/types/PointBundle.h ./RayTracer/types/Vector.cpp $(CFLAGS)
